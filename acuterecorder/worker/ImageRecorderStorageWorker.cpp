//
// Created by Gael Rial Costas on 18/11/2021.
//

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

    const auto number = QString("%1").arg( id , 6 , 10 , QChar( '0' ));
    const auto path = output_.absoluteFilePath(number + ".png");
    image->save( path , "PNG" );
    id++;
  }
}

bool ImageRecorderStorageWorker::popElement( std::shared_ptr< QImage >& image )
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

  image = queue_.takeFirst();

  emit fileQueueSizeChanged( queue_.size( ));
  mutex_.unlock( );

  return true;
}

void ImageRecorderStorageWorker::stop( )
{
  running_ = false;

  mutex_.lock( );
  notEmptyCondition_.wakeAll( );
  mutex_.unlock( );
}

void ImageRecorderStorageWorker::push( std::shared_ptr< QImage > image )
{
  mutex_.lock( );
  queue_.push_back( image );
  emit fileQueueSizeChanged( queue_.size( ));
  mutex_.unlock( );

  notEmptyCondition_.wakeAll( );
}
