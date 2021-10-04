//
// Created by Gael Rial Costas on 8/3/21.
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
 * @param start the TimeStamp marking the startButton of this thread.
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

WidgetRenderThread::WidgetRenderThread( RecorderGeneralData *data )
  :
  AbstractRendererThread( data->getFinalDestinationSize( ) ,
                          data->fps ) ,
  recorderWidget_( data->recorderWidget ) ,
  storageThread_( data->getFinalDestinationSize( ) , data->fps ) ,
  helper_( data->getFinalRenderHelper( )) ,
  start_( ) ,
  timer_( nullptr ) ,
  imagesRendered_( 0 ) ,
  relativeViewport_( data->getFinalRelativeViewport( ))
{

  std::cout << "Widget render thread" << std::endl;
  std::cout << "Source viewport: " << relativeViewport_
            << " (" << data->getFinalSourceViewport( ) << ")" << std::endl;
  std::cout << "Size: " << size_.width( ) << ", "
            << size_.height( ) << std::endl;
  std::cout << "ST Size: " << storageThread_.size( ).width( ) << ", "
            << storageThread_.size( ).height( ) << std::endl;
  std::cout << "------------------------------" << std::endl;

}

bool WidgetRenderThread::start( )
{
  if ( !AbstractRendererThread::start( ) ||
       storageThread_.isThreadRunning( ))
    return false;

  start_ = std::chrono::high_resolution_clock::now( );
  imagesRendered_ = 0;

  auto parent = helper_.widget( ) == nullptr
                ? recorderWidget_
                : helper_.widget( );

  timer_ = new QTimer( parent );
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
  storageThread_.push( helper_.render( size_ , relativeViewport_ ));
}

