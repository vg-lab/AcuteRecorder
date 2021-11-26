//
// Created by gaelr on 18/11/2021.
//

#include "Recorder.h"

#include <QThread>
#include <QDebug>

Recorder::Recorder( RecorderSettings settings ) :
  settings_( std::move( settings )) ,
  active_( true ) ,
  storageWorker_( nullptr )
{

  if ( !settings_.isValid( ))
  {
    qDebug( )
      << "[Recorder] Recorder settings are not valid. Aborting construction";
    settings_.sendInvalidParametersDebugMessage( );
  }
  else
  {
    storageWorker_ = new RecorderStorageWorker(
      this ,
      settings_.getOutputSize( ) ,
      settings_.getFPS( ) ,
      settings_.getOutputPath( )
    );

    QObject::connect(
      storageWorker_ , SIGNAL( finished( )) ,
      storageWorker_ , SLOT( deleteLater( ))
    );

    connect( storageWorker_ ,
             &RecorderStorageWorker::fileQueueSizeChanged ,
             [ & ]( int value )
             { emit bufferSizeChange( value ); } );

    connect( storageWorker_ ,
             &QThread::finished ,
             [ & ]( )
             { emit finished( ); } );
    storageWorker_->start( );
  }
}

bool Recorder::isRecording( ) const
{
  return active_;
}

void Recorder::stop( )
{
  if ( !active_ ) return;
  active_ = false;
  storageWorker_->stop( );
}

void Recorder::takeFrame( )
{
  if ( !active_ ) return;
  auto input = settings_.getInputArea( );
  auto output = settings_.getOutputSize( );
  auto image = settings_.getInput( ).render( input , output );
  storageWorker_->push( image );
}
