//
// Created by gaeqs on 8/3/21.
//

#include "WidgetRenderThread.h"
#include <QtConcurrent/QtConcurrent>
#include <QPainter>
#include <iostream>

/**
 * Prints a debug message with the average velocity of this render thread
 * every 100 images.
 * @param i the amount of images rendered.
 * @param start the timestamp marking the start of this thread.
 */
inline void printDebugVelocity( int i , std::chrono::time_point<
  std::chrono::system_clock , std::chrono::nanoseconds > start )
{
  if ( i % 100 == 0 )
  {
    auto delay = std::chrono::high_resolution_clock::now( ) - start;
    float secs = std::chrono::duration_cast< std::chrono::milliseconds >(
      delay ).count( );
    std::cout << (( i + 1 ) * 1000 / secs ) << " img/s" << std::endl;
  }
}

WidgetRenderThread::WidgetRenderThread( const QSize& size , int fps ,
                                        QWidget *widget )
  :
  AbstractRendererThread( size , fps ) ,
  storageThread_( size , fps ) , widget_( widget )
{

}

bool WidgetRenderThread::start( )
{
  if ( !AbstractRendererThread::start( )) return false;
  storageThread_.start( );
  return true;
}

bool WidgetRenderThread::setFPS( int fps )
{
  if ( !AbstractRendererThread::setFPS( fps )) return false;

  storageThread_.setFPS( fps );

  return true;
}

bool WidgetRenderThread::setSize( const QSize& size )
{
  if ( !AbstractRendererThread::setSize( size )) return false;

  storageThread_.setSize( size );

  return true;
}

VideoStorageThread *WidgetRenderThread::storeManager( )
{
  return &storageThread_;
}

void WidgetRenderThread::run( )
{

  int i = 0;
  auto start = std::chrono::high_resolution_clock::now( );
  auto delay = std::chrono::nanoseconds( 1000000 / fps_ );


  while ( running_ )
  {
    auto then = std::chrono::high_resolution_clock::now( );

    render( );

    // Sleep
    auto time = std::chrono::high_resolution_clock::now( ) - then;
    if ( time < delay )
    {
      std::this_thread::sleep_for( delay - time );
    }

    // Prints the velocity every 100 frames
    printDebugVelocity( i++ , start );
  }

  storageThread_.stop( );
  storageThread_.join( );

  finished_ = true;
}

void WidgetRenderThread::render( )
{
  auto *image = new QImage( size_ , QImage::Format_RGB888 );
  QPainter painter( image );

  // This scales the widget to fit the image.
  painter.scale(( double ) size_.width( ) / widget_->width( ) ,
                ( double ) size_.height( ) / widget_->height( ));

  // Renders and sends the image to the storage thread.
  widget_->render( &painter );
  storageThread_.push( image );
}
