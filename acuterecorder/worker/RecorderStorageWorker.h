//
// Created by gaeqs on 12/14/21.
//

#ifndef ACUTERECORDER_RECORDERSTORAGEWORKER_H
#define ACUTERECORDER_RECORDERSTORAGEWORKER_H

#include <QThread>
#include <acuterecorder/api.h>

class QObject;
class QSize;
class QImage;

/**
 * A storage worker that receives frames and storages them in some way.
 *
 * Default implementations of this class are:
 * - FFMPEGRecorderStorageWorker (Builder name: ffmpeg)
 * - ImageRecorderStorageWorker (Builder name: image)
 */
class ACUTERECORDER_API RecorderStorageWorker : public QThread
{

Q_OBJECT

protected:

  /**
   * Starts the worker.
   * This method does nothing if the worker is already running.
   */
  void run( ) override;

public:

  explicit RecorderStorageWorker( QObject *parent );

  /**
   * Sends a frame to the storage.
   * @param image the frame.
   */
  virtual void push( QImage *image );

public slots:

  /**
   * Stops the worker.
   * This method does nothing if the worker is not running.
   */
  virtual void stop( );

signals:

  /**
   * Notifies a change in the buffer of the worker.
   * @param size the size of the buffer.
   */
  void fileQueueSizeChanged( int size );

};


#endif //ACUTERECORDER_RECORDERSTORAGEWORKER_H
