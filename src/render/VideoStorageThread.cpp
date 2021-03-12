//
// Created by gaeqs on 8/3/21.
//

#include "VideoStorageThread.h"
#include <QtConcurrent/QtConcurrent>
#include <iostream>

const char *BASE_COMMAND = "ffmpeg -r %d -f rawvideo -pix_fmt rgb24 -s %dx%d -i - -c:v libx265 -preset ultrafast -y -crf 21 %s";

/**
 * Generates a FFMPEG command used to encode a set of raw images to a mp4 video.
 * The video will have the given width and height and it will be display at the
 * given framerate (fps). It will be saved at the given output.
 *
 * All raw images must match the given width and height.
 *
 * @param fps the framerate of the video.
 * @param width the width of the video.
 * @param height the height of the video.
 * @param output the output location.
 * @return the FFMPEG command to use.
 */
std::string generateFFMPEGCommand( int fps , int width , int height ,
                                   const std::string& output )
{
  const int ARRAY_SIZE = 2048;
  const char *outputCString = output.c_str( );
  char array[ARRAY_SIZE];

  int size = snprintf( array , ARRAY_SIZE , BASE_COMMAND ,
                       fps , width , height , outputCString );

  return std::string( array , array + size );
}

VideoStorageThread::VideoStorageThread( const QSize& size , int fps ) :
  AbstractRendererThread( size , fps ) ,
  queue_( ) , file_( ) , mutex_( ) , notEmptyCondition_( ) , filesInQueue_( 0 )
{
}

bool VideoStorageThread::start( )
{
  if ( !AbstractRendererThread::start( )) return false;
  future_ = QtConcurrent::run( [ = ]( )
                               { run( ); } );
  return true;
}

void VideoStorageThread::join( )
{
  future_.waitForFinished( );
}

void VideoStorageThread::push( QImage *image )
{
  mutex_.lock( );
  queue_.push_back( image );
  mutex_.unlock( );

  notEmptyCondition_.wakeAll( );
}

int VideoStorageThread::filesInQueue( ) const
{
  return filesInQueue_;
}

std::string VideoStorageThread::output( ) const
{
  return output_;
}


bool VideoStorageThread::setOutput( const std::string& output )
{
  if ( !finished_ ) return false;
  output_ = output;
  return true;
}

void VideoStorageThread::run( )
{
  // Creates the FFMPEG command.
  std::string cmd = generateFFMPEGCommand(
    fps_ ,
    size_.width( ) ,
    size_.height( ) ,
    "output.mp4" );

  // Creates the process for the command and opens a write pipe.
  file_ = popen( cmd.c_str( ) , "w" );

  QImage *image;
  while ( running_ || !queue_.empty( ))
  {

    // Pops an element from t he queue. If this method returns
    // true the thread must end. If that happens we just break the while.
    if ( !popElement( image )) break;

    // Sends the image to FFMPEG.
    unsigned char *bytes = image->bits( );
    int amount = image->byteCount( );
    fwrite( bytes , amount , sizeof( unsigned char ) , file_ );
    delete image;

    filesInQueue_ = queue_.size( );
  }

  fclose( file_ );

  finished_ = true;
}

bool VideoStorageThread::popElement( QImage *& image )
{
  mutex_.lock( );

  // If the queue is empty, this thread waits for a update.
  // If the update is a queue push the thread exits the while.
  // If the update is a render stop the thread must end. In this
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
  mutex_.unlock( );

  return true;
}