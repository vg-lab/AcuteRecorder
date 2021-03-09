//
// Created by gaeqs on 8/3/21.
//

#include "RenderManager.h"
#include <QtConcurrent/QtConcurrent>
#include <QPainter>
#include <iostream>

RenderManager::RenderManager( int fps , QSize size , QWidget *widget ) :
  storeManager_( size , fps ) , fps_( fps ) ,
  size_( size ) , widget_( widget ) ,
  delayPerFrame_( 1000000 / fps ) ,
  finished_( true ) , running_( false )
{

}

bool RenderManager::start( )
{
  if ( !finished_ ) return false;
  running_ = true;
  finished_ = false;

  storeManager_.setFPS( fps_ );
  storeManager_.setSize( size_ );

  QtConcurrent::run( [ = ]( )
                     { run( ); } );
  storeManager_.start( );

  return true;
}

void RenderManager::stop( )
{
  running_ = false;
}

int RenderManager::FPS( ) const
{
  return fps_;
}

bool RenderManager::setFPS( int fps )
{
  if ( !finished_ ) return false;

  fps_ = fps;

  return true;
}

QSize RenderManager::size( )
{
  return size_;
}

bool RenderManager::setSize( QSize size )
{
  if ( !finished_ ) return false;

  size_ = size;

  return true;
}

StoreManager *RenderManager::storeManager( )
{
  return &storeManager_;
}

void RenderManager::run( )
{

  int i = 0;
  auto start = std::chrono::high_resolution_clock::now( );

  while ( running_ )
  {
    auto then = std::chrono::high_resolution_clock::now( );

    render( );

    // Sleep
    auto now = std::chrono::high_resolution_clock::now( );
    auto time = std::chrono::duration_cast< std::chrono::nanoseconds >(
      now - then );
    if ( time < delayPerFrame_ )
    {
      std::this_thread::sleep_for( delayPerFrame_ - time );
    }

    // Prints the velocity every 100 frames
    if ( i++ % 100 == 0 )
    {
      auto delay = std::chrono::high_resolution_clock::now( ) - start;
      float secs = std::chrono::duration_cast< std::chrono::milliseconds >(
        delay ).count( );
      std::cout << ( i * 1000 / secs ) << " img/s" << std::endl;
    }
  }

  storeManager_.stop( );
  storeManager_.join( );

  finished_ = true;
}

void RenderManager::render( )
{
  auto *image = new QImage( size_ , QImage::Format_RGB888 );
  QPainter painter( image );
  painter.scale(( double ) size_.width( ) / widget_->width( ) ,
                ( double ) size_.height( ) / widget_->height( ));
  widget_->render( &painter );

  storeManager_.push( image );
}