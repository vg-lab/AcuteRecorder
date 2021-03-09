//
// Created by gaeqs on 8/3/21.
//

#include "StoreManager.h"
#include <QtConcurrent/QtConcurrent>
#include <iostream>

StoreManager::StoreManager( QSize size , int fps ) :
  queue_( ) , file_( ) , running_( false ) , finished_( true ) ,
  mutex_( ) , notEmptyCondition_( ) , size_( size ) , fps_( fps ) ,
  filesInQueue_( 0 )
{

}


bool StoreManager::start( )
{
  if ( !finished_ ) return false;
  finished_ = false;
  running_ = true;

  future_ = QtConcurrent::run( [ = ]( )
                               { run( ); } );

  return true;
}

void StoreManager::stop( )
{
  running_ = false;

  notEmptyCondition_.wakeAll( );
}

void StoreManager::push( QImage *image )
{
  mutex_.lock( );

  queue_.push_back( image );

  mutex_.unlock( );
  notEmptyCondition_.wakeAll( );
}

void StoreManager::join( )
{
  future_.waitForFinished( );
}

int StoreManager::FPS( ) const
{
  return fps_;
}

bool StoreManager::setFPS( int fps )
{
  if ( !finished_ ) return false;

  fps_ = fps;

  return true;
}

QSize StoreManager::size( )
{
  return size_;
}

bool StoreManager::setSize( QSize size )
{
  if ( !finished_ ) return false;

  size_ = size;

  return true;
}

int StoreManager::filesInQueue( )
{
  return filesInQueue_;
}

void StoreManager::run( )
{
  // Creates the FFMPEG command.
  std::string sizeStr =
    std::to_string( size_.width( )) + "x" + std::to_string( size_.height( ));

  std::string cmd =
    "ffmpeg -r " + std::to_string( fps_ ) + " -f rawvideo -pix_fmt rgb24 -s " +
    sizeStr + " -i -" +
    " -c:v libx265 -preset ultrafast -y -crf 21 output.mp4";

  // Creates the process for the command and opens a write pipe.
  file_ = popen( cmd.c_str( ) , "w" );

  while ( running_ || !queue_.empty( ))
  {

    // Gets the next image from the queue.
    mutex_.lock( );
    while ( queue_.empty( ))
    {
      notEmptyCondition_.wait( &mutex_ );

      if ( queue_.isEmpty( ) && !running_ )
      {
        mutex_.unlock( );
        goto whileEnd;
      }
    }

    auto *image = queue_.front( );
    queue_.pop_front( );
    mutex_.unlock( );

    // Sends the image to FFMPEG.
    unsigned char *bytes = image->bits( );
    int amount = image->byteCount( );
    fwrite( bytes , amount , sizeof( unsigned char ) , file_ );

    delete image;

    filesInQueue_ = queue_.size( );
  }

  whileEnd:
  fclose( file_ );

  finished_ = true;
}