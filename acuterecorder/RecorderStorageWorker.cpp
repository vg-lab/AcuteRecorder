//
// Created by gaelr on 18/11/2021.
//

#include "RecorderStorageWorker.h"

#include <memory>
#include <QImage>
#include <QDebug>
#include <QProcess>

//const char *C_BASE_COMMAND_GPU = "ffmpeg -hwaccel cuda -vsync 0 -r %d -f rawvideo -s %dx%d -pix_fmt rgb24 -i - -c:v hevc_nvenc -f mp4 -preset medium -y %s";
//const char *C_BASE_COMMAND_CPU = "ffmpeg -vsync 0 -r %d -f rawvideo -s %dx%d -pix_fmt rgb24 -i - -c:v libx264 -f mp4 -preset fast -y %s";

constexpr int C_NVIDIA_MIN_DIMENSION = 145;

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
                                   const QString& output )
{

  QStringList arguments;
  // If the width or height are less than 145 pixels, use CPU encoding.
  // This is because NVENC doesn't support video
  // encoding of such small dimensions.
  if ( width < C_NVIDIA_MIN_DIMENSION || height < C_NVIDIA_MIN_DIMENSION )
  {
    arguments << "-vsync" << "0" << "-r" << QString::number( fps );
    arguments << "-f" << "rawvideo" << "-s";
    arguments << QString::number( width ) + "x" + QString::number( height );
    arguments << "-pix_fmt" << "rgb24" << "-i" << "-" << "-c:v" << "libx264";
    arguments << "-f" << "mp4" << "-preset" << "fast" << "-y" << output;
  }
  else
  {
    arguments << "-hwaccel" << "cuda";
    arguments << "-vsync" << "0" << "-r" << QString::number( fps );
    arguments << "-f" << "rawvideo" << "-s";
    arguments << QString::number( width ) + "x" + QString::number( height );
    arguments << "-pix_fmt" << "rgb24" << "-i" << "-" << "-c:v" << "hevc_nvenc";
    arguments << "-f" << "mp4" << "-preset" << "medium" << "-y" << output;
  }

  return arguments;
}

RecorderStorageWorker::RecorderStorageWorker(
  const QSize& size , int fps , QString output ) :
  size_( size ) ,
  fps_( fps ) ,
  output_( std::move( output )) ,
  expectedBytesPerLine_( size.width( ) * 3 ) ,
  mutex_( ) ,
  notEmptyCondition_( ) ,
  queue_( ) ,
  running_( false )
{


}

void RecorderStorageWorker::start( )
{
  if ( running_ ) return;
  running_ = true;


  // Creates the FFMPEG command.
  QStringList arguments = createFFMPEGArguments(
    fps_ ,
    size_.width( ) ,
    size_.height( ) ,
    output_ );

  // Creates the process for the command and opens a write pipe.

  auto process = new QProcess( this );
  process->start( QString( "ffmpeg" ) , arguments , QIODevice::ReadWrite );

  QImage *image;
  while ( running_ || !queue_.empty( ))
  {

    // Pops an element from the queue. If this method returns
    // true the thread must end. If that happens we just break the while.
    if ( !popElement( image )) break;

    // Sends the image to FFMPEG.
    char *bytes = ( char * ) image->bits( );
    auto amount = static_cast<qint64>(image->byteCount( ));

    // Qt images will always ceil the bytes per line to a multiple of four.
    // This is because QImage uses integers under the hood.
    // We need to get rid of these extra bytes or ffmpeg will implode!
    int bytesPerLine = image->bytesPerLine( );
    qint64 difference = bytesPerLine - expectedBytesPerLine_;

    if ( difference )
    {
      // There are extra bytes! Let's get rid of them writing
      // the frame line per line.
      for ( int i = 0; i < size_.height( ); ++i )
      {
        process->write( bytes , expectedBytesPerLine_ * sizeof( char ));
        bytes += bytesPerLine;
      }
    }
    else
    {
      // There are no extra bytes! Write the full frame.

      process->write( bytes , amount * sizeof( char ));
    }
    delete image;
  }

  process->closeWriteChannel();
  process->waitForFinished();

  qDebug() << process->readAllStandardOutput();
  qDebug() << process->readAllStandardError();

  emit finished( );

}

bool RecorderStorageWorker::popElement( QImage *& image )
{
  mutex_.lock( );

  // If the queue is empty, this thread waits for a update.
  // If the update is a queue push the thread exits the while.
  // If the update is a render stopButton the thread must end. In this
  // case this method returns false.
  while ( queue_.empty( ))
  {
    notEmptyCondition_.wait( &mutex_ );

    if ( queue_.isEmpty( ) && !running_ )
    {
      mutex_.unlock( );
      return false;
    }
  }

  image = queue_.front( );

  queue_.pop_front( );
  emit fileQueueSizeChanged( queue_.size( ));
  mutex_.unlock( );

  return true;
}

void RecorderStorageWorker::stop( )
{
  running_ = false;

  mutex_.lock( );
  notEmptyCondition_.wakeAll( );
  mutex_.unlock( );
}

void RecorderStorageWorker::push( QImage *image )
{
  mutex_.lock( );
  queue_.push_back( image );
  emit fileQueueSizeChanged( queue_.size( ));
  mutex_.unlock( );

  notEmptyCondition_.wakeAll( );
}
