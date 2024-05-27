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

#include "ImageRecorderStorageWorker.h"

#include <memory>
#include <QImage>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QString>

ImageRecorderStorageWorker::ImageRecorderStorageWorker( QObject *object ,
                                                        const QString &output )
  : RecorderStorageWorker( object ) ,
    output_( output ) ,
    mutex_( ) ,
    notEmptyCondition_( ) ,
    queue_( ) ,
    running_( false )
{
  if(!output_.exists() || !output_.isReadable())
    throw(std::runtime_error{"The output directory is invalid or doesn't exist!"});
}

void ImageRecorderStorageWorker::run( )
{
  if ( running_ ) return;
  running_ = true;

  std::shared_ptr< QImage > image = nullptr;

  int id = 0;

  while ( running_ || !queue_.empty( ))
  {
    // Pops an element from the queue. If this method returns
    // true the thread must end. If that happens we just break the while.
    if ( !popElement( image )) break;

    const auto number = QString("frame_%1").arg( id , 6 , 10 , QChar( '0' ));
    const auto path = output_.absoluteFilePath(number + ".png");
    if(!image->save( path , "PNG" ))
    {
      error_ = "Unable to save image : " + path;
      emit error(error_);
      break;
    }
    id++;
  }

  running_ = false;
}

bool ImageRecorderStorageWorker::popElement( std::shared_ptr< QImage >& image )
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
      notEmptyCondition_.wait( locker.mutex() );

      if(queue_.isEmpty() && !running_) return false;
    }

    image = queue_.takeFirst();
    qSize = queue_.size();
  }

  emit fileQueueSizeChanged( qSize );

  return true;
}

void ImageRecorderStorageWorker::stop( )
{
  running_ = false;

  QMutexLocker locker(&mutex_);
  notEmptyCondition_.wakeAll( );
}

void ImageRecorderStorageWorker::push( std::shared_ptr< QImage > image )
{
  int qSize = 0;

  // Do not push images if not running.
  if(running_)
  {
    QMutexLocker locker(&mutex_);
    queue_.push_back( image );
    qSize = queue_.size();
  }

  emit fileQueueSizeChanged( qSize );

  notEmptyCondition_.wakeAll( );
}
