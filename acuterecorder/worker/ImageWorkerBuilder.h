//
// Created by gaeqs on 12/15/21.
//

#ifndef ACUTERECORDER_IMAGEWORKERBUILDER_H
#define ACUTERECORDER_IMAGEWORKERBUILDER_H

#include "WorkerBuilder.h"

/**
 * Builder for ImageRecorderStorageWorkers.
 */
class ImageWorkerBuilder : public WorkerBuilder
{
public:

  ImageWorkerBuilder( );

  bool isAvailable() const override;

  RecorderStorageWorker *createWorker(
    QObject *object , RecorderSettings& settings ) const override;
};


#endif //ACUTERECORDER_IMAGEWORKERBUILDER_H
