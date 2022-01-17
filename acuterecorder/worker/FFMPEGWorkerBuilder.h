//
// Created by gaeqs on 12/15/21.
//

#ifndef ACUTERECORDER_FFMPEGWORKERBUILDER_H
#define ACUTERECORDER_FFMPEGWORKERBUILDER_H


#include "WorkerBuilder.h"

/**
 * Builder for FFMPEGRecorderStorageWorkers.
 *
 * This builder may be unavailable if ffmpeg is not installed in the machine.
 */
class FFMPEGWorkerBuilder : public WorkerBuilder
{
public:

  FFMPEGWorkerBuilder( );

  bool isAvailable( ) const override;

  RecorderStorageWorker *createWorker(
    QObject *object , const RecorderSettings& settings ) const override;

};


#endif //ACUTERECORDER_FFMPEGWORKERBUILDER_H
