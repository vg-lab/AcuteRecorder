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
    QObject *object , RecorderSettings& settings ) const override;

  mutable QStringList codecs; /** available codecs. */
};


#endif //ACUTERECORDER_FFMPEGWORKERBUILDER_H
