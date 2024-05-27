/*
 * Copyright (c) 2021-2024 VG-Lab/URJC.
 *
 * Authors: Gael Rial Costas <gael.rial.costas@urjc.es>
 *
 * This file is part of AcuteRecorder <https://github.com/vg-lab/AcuteRecorder>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "FFMPEGRecorderStorageWorker.h"

// C++
#include <memory>
#include <fstream>

// Qt
#include <QImage>
#include <QMutex>
#include <QProcess>
#include <QVariant>
#include <QFile>
#include <QFileInfo>

const QString FFMPEGRecorderStorageWorker::CODECS_KEY = "ffmpeg_codec";
const QString SUFFIX = "_temporal";

/**
 * Generates a FFMPEG command used to encode a set of raw images to a H.264 or MPEG-4 P2 video.
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
  constexpr int C_VAAPI_MIN_DIMENSION = 32;
  QStringList arguments;

  if(codecs.contains("h264_nvenc"))
  {
    // If the width or height is less than 145 pixels fallback to another encoder.
    // This is because NVENC doesn't support video
    // encoding of such small dimensions.
    if (width >= C_NVIDIA_MIN_DIMENSION && height >= C_NVIDIA_MIN_DIMENSION)
    {
      arguments << "-hwaccel" << "cuda";
      arguments << "-vsync" << "passthrough" << "-r" << QString::number( fps );
      arguments << "-f" << "rawvideo" << "-s";
      arguments << QString::number( width ) + "x" + QString::number( height );
      arguments << "-pix_fmt" << "rgb24" << "-i" << (output+SUFFIX) << "-c:v" << "h264_nvenc";
      arguments << "-f" << "matroska" << "-preset" << "medium" << "-y" << output;
    }
  }

  if(codecs.contains("h264_vaapi") && arguments.isEmpty())
  {
    // Do not exceed hardware constraints.
    if (width >= C_VAAPI_MIN_DIMENSION && height >= C_VAAPI_MIN_DIMENSION)
    {
      arguments << "-hwaccel" << "vaapi" << "-hwaccel_output_format" << "vaapi";
      arguments << "-vsync" << "passthrough" << "-r" << QString::number( fps );
      arguments << "-f" << "rawvideo" << "-s";
      arguments << QString::number( width ) + "x" + QString::number( height );
      arguments << "-pix_fmt" << "rgb24" << "-i" << (output+SUFFIX);
      arguments << "-vf" << "format=nv12,hwupload" << "-c:v" << "h264_vaapi";
      arguments << "-f" << "matroska" << "-qp" << "24" << "-y" << output;
    }
  }

  if(codecs.contains("libx264") && arguments.isEmpty())
  {
    arguments << "-vsync" << "passthrough" << "-r" << QString::number( fps );
    arguments << "-f" << "rawvideo" << "-s";
    arguments << QString::number( width ) + "x" + QString::number( height );
    arguments << "-pix_fmt" << "rgb24" << "-i" << (output+SUFFIX) << "-c:v" << "libx264";
    arguments << "-f" << "matroska" << "-preset" << "fast" << "-y" << output;
  }

  if(codecs.contains("mpeg4") && arguments.isEmpty())
  {
    arguments << "-vsync" << "passthrough" << "-r" << QString::number( fps );
    arguments << "-f" << "rawvideo" << "-s";
    arguments << QString::number( width ) + "x" + QString::number( height );
    arguments << "-pix_fmt" << "rgb24" << "-i" << (output+SUFFIX) << "-c:v" << "mpeg4";
    arguments << "-f" << "matroska" << "-qscale:v" << "1" << "-y" << output;
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
  const auto temporalOutput = output_ + SUFFIX;
  QFile::remove(temporalOutput);

  // Creates the FFMPEG command.
  const QStringList arguments = createFFMPEGArguments(
    fps_ ,
    size_.width( ) ,
    size_.height( ) ,
    output_,
    codecs_);

  std::ofstream temporalfile (temporalOutput.toStdString().c_str(),
                              std::ofstream::binary|std::ofstream::trunc);

  if(!temporalfile.is_open())
  {
    error_ = "Unable to open temporal file:" + temporalOutput;
    emit error(error_);
    return;
  }

  std::shared_ptr< QImage > image = nullptr;
  while ( (running_ || !queue_.empty( )) )
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
        temporalfile.write( bytes , expectedBytesPerLine_ * sizeof( char ));
        bytes += bytesPerLine;
      }
    }
    else
    {
      // There are no extra bytes! Write the full frame.
      temporalfile.write( bytes , amount * sizeof( char ));
    }

    if(!temporalfile.good())
    {
      error_ = "Failure when writing to temporal file: " + temporalOutput;
      emit error(error_);
      break;
    }
  }

  temporalfile.flush();
  temporalfile.close();

  if(error_.isEmpty())
  {
    bool errorOcurred = false;

    QProcess process;
    connect(&process, &QProcess::errorOccurred, [&errorOcurred](){ errorOcurred = true; });
    process.start( QString( "ffmpeg" ) , arguments , QIODevice::ReadWrite|QIODevice::Unbuffered );
    process.waitForStarted(-1);
    process.waitForFinished( -1 );

    if(errorOcurred)
    {
      error_ = process.errorString();
      emit error(error_);
    }
  }

  if(!QFile::remove(temporalOutput) && error_.isEmpty())
  {
    error_ = "Unable to remove temporal file: " + temporalOutput;
    emit error(error_);
  }

  running_ = false;
}

bool FFMPEGRecorderStorageWorker::popElement( std::shared_ptr< QImage >& image )
{
  int qSize = 0;

  {
    QMutexLocker locker(&mutex_);

    // If the queue is empty, this thread waits for a update.
    // If the update is a queue push the thread exits the while.
    // If the update is a render stopButton the thread must end. In this
    // case this method returns false.
    while ( queue_.empty( ))
    {
      notEmptyCondition_.wait( &mutex_ );

      if (!running_ && queue_.empty() ) return false;
    }

    image = queue_.takeFirst();
    qSize = queue_.size();
  }

  emit fileQueueSizeChanged( qSize );

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
  int qSize = 0;

  // do not insert frames if not running
  if(running_)
  {
    QMutexLocker locker(&mutex_);
    queue_.push_back( image );
    qSize = queue_.size();
  }

  emit fileQueueSizeChanged( qSize );

  notEmptyCondition_.wakeAll( );
}
