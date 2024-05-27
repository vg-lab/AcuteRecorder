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
   * @param settings the settings of the recorder. Can be modified by builder.
   * @return the new worker.
   */
  virtual RecorderStorageWorker *createWorker(
    QObject *object , RecorderSettings& settings ) const = 0;

private:
  bool outputToFolder_;

};


#endif //ACUTERECORDER_WORKERBUILDER_H
