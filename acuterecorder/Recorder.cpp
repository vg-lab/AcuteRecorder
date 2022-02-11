//
// Created by Gael Rial Costas on 18/11/2021.
//

#include "Recorder.h"

#include <QThread>
#include <QDebug>
#include <QImage>

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

Recorder::Recorder( RecorderSettings settings )
  :
  settings_( std::move( settings ))
  , storageWorker_( nullptr )
  , last_frame_( )
  , delayBetweenFrames_( 1000000000L / static_cast<int64_t>(settings.getFPS( )))
  , duplicationDelay_( 0 )
  , recording_( false )
{

  if ( !settings_.isValid( ))
  {
    qDebug( )
      << "[Recorder] Recorder settings are not valid. Aborting construction";
    settings_.invalidParametersDebug( );
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

      QObject::connect( storageWorker_ , SIGNAL( finished( )) ,
                        storageWorker_ , SLOT( deleteLater( ))
      );

      connect( storageWorker_ , SIGNAL( fileQueueSizeChanged( int )) ,
               this , SIGNAL( bufferSizeChange( int )));

      connect( storageWorker_ , SIGNAL( finished( )) ,
               this , SIGNAL( finished( )));

      recording_ = true;
      storageWorker_->start( );
      last_frame_ = std::chrono::high_resolution_clock::now( );
    }
  }
}

bool Recorder::isRecording( ) const
{
  return recording_;
}

bool Recorder::hasFinished( )
{
  return !storageWorker_->isRunning( );
}

void Recorder::stop( )
{
  if ( !isRecording( )) return;

  storageWorker_->stop( );
  recording_ = false;
}

void Recorder::wait( )
{
  storageWorker_->wait( );
}

void Recorder::takeFrame( )
{
  if ( !isRecording( )) return;
  bool stabilize = settings_.shouldStabilizeFramerate( );
  if ( stabilize )
  {
    auto now = std::chrono::high_resolution_clock::now( );
    duplicationDelay_ += now - last_frame_ - delayBetweenFrames_;
    last_frame_ = now;

    if ( duplicationDelay_ < -delayBetweenFrames_)
    {
      // Frame not needed! Skipped!
      duplicationDelay_ += delayBetweenFrames_;
      return;
    }
  }

  auto input = settings_.getInputArea( );
  auto output = settings_.getOutputSize( );
  auto image = settings_.getInput( ).render( input , output );

  while ( stabilize && duplicationDelay_ > delayBetweenFrames_ )
  {
    // Create duplicated image pointing the data of the original
    storageWorker_->push( new QImage( *image ));
    duplicationDelay_ -= delayBetweenFrames_;
  }

  storageWorker_->push( image );
}
