/*
 * Copyright (c) 2021-2024 VG-Lab/URJC.
 *
 * Authors: Gael Rial Costas <gael.rial.costas@urjc.es>
 *
 * This file is part of AcuteRecorder <https://github.com/vg-lab/AcuteRecorder>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

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

      connect( storageWorker_ , SIGNAL(error(const QString &)),
               this, SIGNAL(error(const QString &)));

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

  const bool stabilize = settings_.shouldStabilizeFramerate( );
  if ( stabilize )
  {
    const auto now = std::chrono::high_resolution_clock::now( );
    duplicationDelay_ += now - last_frame_ - delayBetweenFrames_;
    last_frame_ = now;

    if ( duplicationDelay_ < -delayBetweenFrames_)
    {
      // Frame not needed! Skipped!
      duplicationDelay_ += delayBetweenFrames_;
      return;
    }
  }

  const auto inputArea = settings_.getInputArea( );
  const auto outputSize = settings_.getOutputSize( );
  const auto image = settings_.getInput( ).render( inputArea , outputSize );

  while ( stabilize && duplicationDelay_ > delayBetweenFrames_ )
  {
    // Create duplicated image pointing the data of the original
    storageWorker_->push( image );
    duplicationDelay_ -= delayBetweenFrames_;
  }

  storageWorker_->push( image );
}
