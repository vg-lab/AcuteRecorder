//
// Created by gaelr on 18/11/2021.
//

#include "Recorder.h"

#include <QThread>
#include <QDebug>

#include <worker/ImageWorkerBuilder.h>
#include <worker/FFMPEGWorkerBuilder.h>

WorkerBuilderMap Recorder::registeredWorkers_ = {
  { "image" ,  new ImageWorkerBuilder( ) } ,
  { "ffmpeg" , new FFMPEGWorkerBuilder( ) }
};

void Recorder::registerWorker(
  const QString& worker , WorkerBuilder *builder )
{
  registeredWorkers_[ worker ] = builder;
}

void Recorder::unregisterWorker( const QString& worker )
{
  registeredWorkers_.erase( worker );
}

std::map< QString , WorkerBuilder * > Recorder::getWorkerBuilders( )
{
  return registeredWorkers_;
}

WorkerBuilder *Recorder::getWorkerBuilder( const QString& worker )
{
  return registeredWorkers_[ worker ];
}

Recorder::Recorder( RecorderSettings settings ) :
  settings_( std::move( settings )) ,
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
    auto workerBuilder = getWorkerBuilder( settings_.getStorageWorker( ));
    if ( workerBuilder == nullptr || !workerBuilder->isAvailable( ))
    {
      if ( workerBuilder == nullptr )
      {
        qDebug( ) << "[Recorder] Couldn't find worker "
                  << settings.getStorageWorker( ) << ".";
      }
      else
      {
        qDebug( ) << "[Recorder] Worker " << settings.getStorageWorker( )
                  << " is not available.";
      }
    }
    else
    {
      storageWorker_ = workerBuilder->createWorker( this , settings_ );

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
}

void Recorder::stop( )
{
  if ( !isRecording( )) return;

  storageWorker_->stop( );
}

void Recorder::takeFrame( )
{
  if ( !isRecording( )) return;
  auto input = settings_.getInputArea( );
  auto output = settings_.getOutputSize( );
  auto image = settings_.getInput( ).render( input , output );
  storageWorker_->push( image );
}