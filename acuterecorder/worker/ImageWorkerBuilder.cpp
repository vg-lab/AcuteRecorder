//
// Created by gaeqs on 12/15/21.
//

#include <worker/ImageRecorderStorageWorker.h>
#include <RecorderSettings.h>

#include "ImageWorkerBuilder.h"

ImageWorkerBuilder::ImageWorkerBuilder( ) : WorkerBuilder( true )
{ }

bool ImageWorkerBuilder::isAvailable( ) const
{
  return true;
}

RecorderStorageWorker *ImageWorkerBuilder::createWorker(
  QObject *object , const RecorderSettings& settings ) const
{
  return new ImageRecorderStorageWorker(object, settings.getOutputPath());
}
