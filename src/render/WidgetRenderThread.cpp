//
// Created by gaeqs on 8/3/21.
//

#include "WidgetRenderThread.h"
#include <QtConcurrent/QtConcurrent>
#include <QPainter>
#include <iostream>
#include <thread>

/**
 * Prints a debug message with the average velocity of this render thread
 * every 100 images.
 * @param i the amount of images rendered.
 * @param start the TimeStamp marking the start of this thread.
 */
inline void printDebugVelocity( int i , TimeStamp start )
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
  storageThread_( size , fps ) , widget_( widget ) ,
  start_( ) ,
  timer_( nullptr ) , imagesRendered_( 0 )
{

}

bool WidgetRenderThread::start( )
{
  if ( !AbstractRendererThread::start( ) ||
       storageThread_.isThreadRunning( ))
    return false;

  start_ = std::chrono::high_resolution_clock::now( );
  imagesRendered_ = 0;

  timer_ = new QTimer( widget_ );
  QObject::connect( timer_ , &QTimer::timeout ,
                    [ = ]( )
                    { run( ); } );
  timer_->start( 1000 / fps_ );

  storageThread_.start( );
  return true;
}

void WidgetRenderThread::stop( )
{
  AbstractRendererThread::stop( );
  if ( timer_ != nullptr )
  {
    timer_->stop( );
    finished_ = true;
    delete timer_;
  }

  storageThread_.stop( );
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
  render( );
  printDebugVelocity( imagesRendered_++ , start_ );
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