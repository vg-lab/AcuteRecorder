//
// Created by gaeqs on 12/3/21.
//

#include <QtConcurrent/QtConcurrent>
#include "AbstractRendererThread.h"

AbstractRendererThread::AbstractRendererThread( const QSize& size , int fps ) :
  size_( size ) , fps_( fps ) , running_( false ) , finished_( true )
{

}


bool AbstractRendererThread::start( )
{
  if ( !finished_ ) return false;
  finished_ = false;
  running_ = true;

  future_ = QtConcurrent::run( [ = ]( )
                               { run( ); } );

  return true;
}

void AbstractRendererThread::stop( )
{
  running_ = false;
}

bool AbstractRendererThread::isThreadRunning( ) const
{
  // Use finished_ instead of running_!
  return !finished_;
}

void AbstractRendererThread::join( )
{
  future_.waitForFinished( );
}


int AbstractRendererThread::FPS( ) const
{
  return fps_;
}

bool AbstractRendererThread::setFPS( int fps )
{
  if ( !finished_ ) return false;

  fps_ = fps;

  return true;
}

QSize AbstractRendererThread::size( ) const
{
  return size_;
}

bool AbstractRendererThread::setSize( const QSize& size )
{
  if ( !finished_ ) return false;

  size_ = size;

  return true;
}