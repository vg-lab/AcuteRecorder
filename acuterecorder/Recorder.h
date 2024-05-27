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

#ifndef ACUTERECORDER_RECORDER_H
#define ACUTERECORDER_RECORDER_H

#include <chrono>

#include <acuterecorder/api.h>
#include <acuterecorder/worker/WorkerBuilder.h>
#include <acuterecorder/worker/RecorderStorageWorker.h>

#include <QObject>


#include "RecorderSettings.h"

class RecorderSettings;

typedef std::map< QString , WorkerBuilder * > WorkerBuilderMap;

/**
 * Represents a Recorder.
 *
 * On creation, a recorder setups itself automatically using the given
 * RecorderSettings. Use the slot Recorder::takeFrame() to render the video.
 *
 * The Recorder will automatically render the input element and store the
 * screenshot in the video.
 */
class ACUTERECORDER_API Recorder : public QObject
{
Q_OBJECT

  static WorkerBuilderMap registeredWorkers_;

  RecorderSettings settings_;
  RecorderStorageWorker *storageWorker_;

  std::chrono::time_point<std::chrono::high_resolution_clock> last_frame_;
  std::chrono::nanoseconds delayBetweenFrames_;
  std::chrono::nanoseconds duplicationDelay_;

  bool recording_;

public:

  /**
   * Registers a new worker.
   * @param worker the name of the worker.
   * @param builder the builder of the worker.
   */
  static void registerWorker(
    const QString& worker , WorkerBuilder *builder );

  /**
   * Unregisters a present worker.
   * @param worker the name of the worker to remove.
   */
  static void unregisterWorker( const QString& worker );

  /**
   * Returns a vector with the registered workers.
   * @return the workers.
   */
  static std::map< QString , WorkerBuilder * > getWorkerBuilders( );

  /**
   * Returns the worker builder that matches the given name.
   * @param worker the name.
   * @return the worker or null if not found.
   */
  static WorkerBuilder *getWorkerBuilder( const QString& worker );

  /**
   * Crates the Recorder.
   *
   * The recorder will be ready to use when the
   * invocation of this construction ends.
   *
   * @param settings the settings of the recorder.
   */
  explicit Recorder( RecorderSettings settings );

  /**
   * Returns whether this recorder is recording.
   *
   * Use Recorder::stop() to stop the recording.
   *
   * @return whether this recorder is recording.
   */
  bool isRecording( ) const;

  /**
   * Returns whether this recorder is not recording and
   * the worker has stopped its activity.
   * @return whether this recorder is not recording and
   * the worker has stopped.
   */
  bool hasFinished();

public slots:

  /**
   * Signals the Recorder, making it to record a frame.
   *
   * You can use this slot in a QTimer.
   */
  void takeFrame( );

  /**
   * Signals the Recorder, making it stop the recording.
   *
   * If this Recorder is not recording or is already stopping, this
   * slot does nothing.
   *
   * The recorder may be still recording when the invocation of this
   * slot returns. Use the signal Recorder::finished() if you want
   * to know when the recorder stops.
   *
   */
  void stop( );

  /**
   * Blocks the calling thread until this recording has finished.
   */
  void wait( );

signals:

  /**
   * Notifies a change in the frame buffer size.
   * @param value the buffer size.
   */
  void bufferSizeChange( int value );

  /**
   * Notifies the termination of the recording.
   */
  void finished( );

  /** \brief Notifies about a worker error.
   *
   */
  void error(const QString &message);

};

#endif //ACUTERECORDER_RECORDER_H
