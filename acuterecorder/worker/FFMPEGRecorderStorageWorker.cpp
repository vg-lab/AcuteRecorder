//
// Created by Gael Rial Costas on 18/11/2021.
//

#include "FFMPEGRecorderStorageWorker.h"

#include <memory>
#include <QImage>
#include <QMutex>
#include <QProcess>
#include <QVariant>
#include <QFile>
#include <QFileInfo>

const QString FFMPEGRecorderStorageWorker::CODECS_KEY = "ffmpeg_codec";
const QString SUFFIX = "_temporal";

/**
 * Generates a FFMPEG command used to encode a set of raw images to a mp4 video.
 * The video will have the given width and height and it will be display at the
 * given framerate (fps). It will be saved at the given output.
 *
 * All raw images must match the given width and height.
 *
 * @param fps the framerate of the video.
 * @param width the width of the video.S
 * @param height the height of the video.
 * @param output the output location.
 * @return the FFMPEG command to use.
 */
QStringList createFFMPEGArguments( int fps , int width , int height ,
                                   const QString& output , const QStringList &codecs)
{
  constexpr int C_NVIDIA_MIN_DIMENSION = 145;
  QStringList arguments;

  if(codecs.contains("nvenc_h264"))
  {
    // If the width or height are less than 145 pixels, use CPU encoding.
    // This is because NVENC doesn't support video
    // encoding of such small dimensions.
    if (width >= C_NVIDIA_MIN_DIMENSION && height >= C_NVIDIA_MIN_DIMENSION)
    {
      arguments << "-hwaccel" << "cuda";
      arguments << "-vsync" << "0" << "-r" << QString::number( fps );
      arguments << "-f" << "rawvideo" << "-s";
      arguments << QString::number( width ) + "x" + QString::number( height );
      arguments << "-pix_fmt" << "rgb24" << "-i" << "-" << "-c:v" << "nvenc_h264";
      arguments << "-f" << "mp4" << "-preset" << "medium" << "-y" << output;
    }
  }

  if(codecs.contains("libx264") && arguments.isEmpty())
  {
    arguments << "-vsync" << "0" << "-r" << QString::number( fps );
    arguments << "-f" << "rawvideo" << "-s";
    arguments << QString::number( width ) + "x" + QString::number( height );
    arguments << "-pix_fmt" << "rgb24" << "-i" << "-" << "-c:v" << "libx264";
    arguments << "-f" << "mp4" << "-preset" << "fast" << "-y" << output;
  }

  if(codecs.contains("mpeg4") && arguments.isEmpty())
  {
    arguments << "-vsync" << "0" << "-r" << QString::number( fps );
    arguments << "-f" << "rawvideo" << "-s";
    arguments << QString::number( width ) + "x" + QString::number( height );
    arguments << "-pix_fmt" << "rgb24" << "-i" << "-" << "-c:v" << "mpeg4";
    arguments << "-f" << "mp4" << "-qscale:v" << "1" << "-y" << output;
  }

  Q_ASSERT(!arguments.isEmpty());
  return arguments;
}

FFMPEGRecorderStorageWorker::FFMPEGRecorderStorageWorker(
  QObject *object , const RecorderSettings &settings ) :
  RecorderStorageWorker( object ) ,
  size_( settings.getOutputSize()) ,
  fps_( settings.getFPS() ) ,
  output_( settings.getOutputPath() ) ,
  expectedBytesPerLine_( size_.width( ) * 3 ) ,
  mutex_( ) ,
  notEmptyCondition_( ) ,
  queue_( ) ,
  running_( false )
{
  codecs_ = settings.getExtraSetting(FFMPEGRecorderStorageWorker::CODECS_KEY).toStringList();
  Q_ASSERT(!codecs_.isEmpty());
}

void FFMPEGRecorderStorageWorker::run( )
{
  if ( running_ ) return;
  running_ = true;

  if(QFileInfo::exists(output_) && !QFile::remove(output_))
  {
    error_ = "Unable to remove old output file: " + output_;
    emit error(error_);
  }

  // just in case a crash occurred before, remove temporal silently
  QFile::remove(output_+SUFFIX);

  // Creates the FFMPEG command.
  const QStringList arguments = createFFMPEGArguments(
    fps_ ,
    size_.width( ) ,
    size_.height( ) ,
    output_ + SUFFIX,
    codecs_);

  bool errorOcurred = false;

  // Creates the process for the command and opens a write pipe.
  QProcess process;
  connect(&process, &QProcess::errorOccurred, [&errorOcurred](){ errorOcurred = true; });
  process.start( QString( "ffmpeg" ) , arguments , QIODevice::ReadWrite );

  std::shared_ptr< QImage > image = nullptr;
  while ( (running_ || !queue_.empty( )) && !errorOcurred)
  {
    // Pops an element from the queue. If this method returns
    // true the thread must end. If that happens we just break the while.
    if ( !popElement( image )) break;

    // Sends the image to FFMPEG.
    auto bytes = reinterpret_cast<const char *>(image->bits( ));

    // Qt images will always ceil the bytes per line to a multiple of four.
    // This is because QImage uses integers under the hood.
    // We need to get rid of these extra bytes or ffmpeg will implode!
    const int bytesPerLine = image->bytesPerLine( );
    const auto amount = static_cast<qint64>(bytesPerLine * image->height( ));
    const qint64 difference = bytesPerLine - expectedBytesPerLine_;

    if ( difference )
    {
      // There are extra bytes! Let's get rid of them writing
      // the frame line per line.
      for ( int i = 0; i < size_.height( ); ++i )
      {
        process.write( bytes , expectedBytesPerLine_ * sizeof(char));
        bytes += bytesPerLine;
      }
    }
    else
    {
      // There are no extra bytes! Write the full frame.
      process.write( bytes , amount * sizeof(char));
    }
  }

  if(errorOcurred)
  {
    error_ = process.errorString();
    emit error(error_);
  }

  process.closeWriteChannel( );
  process.waitForFinished( -1 );

  if(!QFile::rename(output_ + SUFFIX, output_))
  {
    error_ = "Unable to rename temporal file to: " + output_;
    emit error(error_);
  }
}

bool FFMPEGRecorderStorageWorker::popElement( std::shared_ptr< QImage >& image )
{
  QMutexLocker locker(&mutex_);

  // If the queue is empty, this thread waits for a update.
  // If the update is a queue push the thread exits the while.
  // If the update is a render stopButton the thread must end. In this
  // case this method returns false.
  while ( queue_.empty( ))
  {
    notEmptyCondition_.wait( &mutex_ );

    if ( queue_.isEmpty( ) && !running_ )
    {
      return false;
    }
  }

  image = queue_.takeFirst();

  emit fileQueueSizeChanged( queue_.size( ));

  return true;
}

void FFMPEGRecorderStorageWorker::stop( )
{
  running_ = false;

  QMutexLocker locker(&mutex_);
  notEmptyCondition_.wakeAll( );
}

void FFMPEGRecorderStorageWorker::push( std::shared_ptr< QImage > image )
{
  {
    QMutexLocker locker(&mutex_);
    queue_.push_back( image );
    emit fileQueueSizeChanged( queue_.size( ));
  }

  notEmptyCondition_.wakeAll( );
}
