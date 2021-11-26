//
// Created by gaelr on 18/11/2021.
//

#ifndef ACUTERECORDER_RECORDER_H
#define ACUTERECORDER_RECORDER_H


#include <QObject>

#include "RecorderSettings.h"
#include "RecorderStorageWorker.h"

class RecorderSettings;

/**
 * Represents a Recorder.
 *
 * On creation, a recorder setups itself automatically using the given
 * RecorderSettings. Use the slot Recorder::takeFrame() to render the video.
 *
 * The Recorder will automatically render the input element and store the
 * screenshot in the video.
 */
class Recorder : public QObject
{
Q_OBJECT
  RecorderSettings settings_;
  RecorderStorageWorker* storageWorker_;

public:
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
  inline bool isRecording( ) const
  { return storageWorker_->isRunning(); }

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

};


#endif //ACUTERECORDER_RECORDER_H
