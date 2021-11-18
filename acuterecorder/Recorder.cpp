//
// Created by gaelr on 18/11/2021.
//

#include "Recorder.h"

#include <utility>
#include <QThread>

Recorder::Recorder( RecorderSettings settings ) :
  settings_( std::move( settings )) ,
  active_( true ) ,
  storageWorker_( settings.getOutputSize( ) , settings.getFps( ) ,
                  settings.getOutputPath( ))
{
  auto *thread = new QThread( );
  storageWorker_.moveToThread( thread );

  connect( thread , SIGNAL( started( QPrivateSignal )) ,
           &storageWorker_ , SLOT( start( )));
  connect( &storageWorker_ , SIGNAL( finished( )) ,
           thread , SLOT( quit( )));
  connect( &storageWorker_ , SIGNAL( finished( )) ,
           &storageWorker_ , SLOT( deleteLater( )));
  connect( thread , SIGNAL( finished( )) ,
           thread , SLOT( deleteLater( )));

  connect( &storageWorker_ ,
           &RecorderStorageWorker::fileQueueSizeChanged ,
           [ & ]( int value )
           { emit bufferSizeChange( value ); } );

  connect( &storageWorker_ ,
           &RecorderStorageWorker::finished ,
           [ & ]( )
           { emit finished( ); } );

  thread->start( );
}

bool Recorder::isRecording( ) const
{
  return active_;
}

void Recorder::stop( )
{
  if ( !active_ ) return;
  active_ = false;
  storageWorker_.stop( );
}

void Recorder::takeFrame( )
{
  auto input = settings_.getInputArea( );
  auto output = settings_.getOutputSize( );
  auto image = settings_.getInput( ).render( input , output );
  storageWorker_.push( image );
}
