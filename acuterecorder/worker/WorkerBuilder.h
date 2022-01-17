//
// Created by gaeqs on 12/15/21.
//

#ifndef ACUTERECORDER_WORKERBUILDER_H
#define ACUTERECORDER_WORKERBUILDER_H

#include "RecorderStorageWorker.h"

class RecorderSettings;

/**
 * Helper class used to create RecorderStorageWorkers.
 * This class also informs about general information about its workers.
 */
class ACUTERECORDER_API WorkerBuilder
{

public:

  /**
   * Creates the builder.
   * @param outputToFolder whether the workers of this builder requires
   * an output folder instead of a file.
   */
  explicit WorkerBuilder( bool outputToFolder );

  virtual ~WorkerBuilder( ) = default;

  /**
   * @return whether the workers of this builder requires
   * an output folder instead of a file.
   */
  bool isOutputAFolder( ) const;

  /**
   * @return whether this builder is available in this machine.
   */
  virtual bool isAvailable( ) const = 0;

  /**
   * Creates a new worker.
   * @param object the parent object of the builder.
   * @param settings the settings of the recorder.
   * @return the new worker.
   */
  virtual RecorderStorageWorker *createWorker(
    QObject *object , const RecorderSettings& settings ) const = 0;

private:
  bool outputToFolder_;

};


#endif //ACUTERECORDER_WORKERBUILDER_H
