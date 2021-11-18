//
// Created by Gael Rial Costas on 8/3/21.
//

#include <VideoStorageThread.h>

#include <iostream>

#include <QtConcurrent/QtConcurrent>

const char *BASE_COMMAND_GPU = "ffmpeg -hwaccel cuda -vsync 0 -r %d -f rawvideo -s %dx%d -pix_fmt rgb24 -i - -c:v hevc_nvenc -f mp4 -preset medium -y %s";
const char *BASE_COMMAND_CPU = "ffmpeg -vsync 0 -r %d -f rawvideo -s %dx%d -pix_fmt rgb24 -i - -c:v libx264 -f mp4 -preset fast -y %s";

constexpr int NVIDIA_MIN_DIMENSION = 145;

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

  // If the width or height are less than 145 pixels, use CPU encoding.
  // This is because NVENC doesn't support video
  // encoding of such small dimensions.
  const char *command;
  if ( width < NVIDIA_MIN_DIMENSION || height < NVIDIA_MIN_DIMENSION )
    command = BASE_COMMAND_CPU;
  else
    command = BASE_COMMAND_GPU;

  int size = snprintf( array , ARRAY_SIZE , command ,
                       fps , width , height , outputCString );

  return { array , array + size };
}

VideoStorageThread::VideoStorageThread( const QSize& size , int fps ) :
  AbstractRendererThread( size , fps ) ,
  queue_( ) , file_( ) , mutex_( ) , notEmptyCondition_( ) ,
  expectedBytesPerLine( size.width( ) * 3 ) ,
  filesInQueue_( 0 )
{
}

bool VideoStorageThread::setSize( const QSize& size )
{
  if ( !AbstractRendererThread::setSize( size )) return false;
  expectedBytesPerLine = size.width( ) * 3;
  return true;
}

bool VideoStorageThread::start( )
{
  if ( !AbstractRendererThread::start( )) return false;
  future_ = QtConcurrent::run( [ = ]( )
                               { run( ); } );
  return true;
}

void VideoStorageThread::stop( )
{
  AbstractRendererThread::stop( );
  notEmptyCondition_.wakeAll( );
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

  std::cout << "Opening FFMPEG" << std::endl;
  std::cout << cmd << std::endl;

  // Creates the process for the command and opens a write pipe.
  file_ = popen( cmd.c_str( ) , "w" );

  QImage *image;
  while ( running_ || !queue_.empty( ))
  {

    // Pops an element from the queue. If this method returns
    // true the thread must end. If that happens we just break the while.
    if ( !popElement( image )) break;

    // Sends the image to FFMPEG.
    unsigned char *bytes = image->bits( );
    int amount = image->byteCount();

    // Qt images will always ceil the bytes per line to a multiple of four.
    // This is because QImage uses integers under the hood.
    // We need to get rid of these extra bytes or ffmpeg will implode!
    int bytesPerLine = image->bytesPerLine( );
    int difference = bytesPerLine - expectedBytesPerLine;

    if ( difference )
    {
      // There are extra bytes! Let's get rid of them writing
      // the frame line per line.
      for ( int i = 0; i < size_.height( ); ++i )
      {
        fwrite( bytes , expectedBytesPerLine ,
                sizeof( unsigned char ) , file_ );
        bytes += bytesPerLine;
      }
    }
    else
    {
      // There are no extra bytes! Write the full frame.
      fwrite( bytes , amount , sizeof( unsigned char ) , file_ );
    }
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
  mutex_.unlock( );

  return true;
}
