//
// Created by gaelr on 18/11/2021.
//

#ifndef ACUTERECORDER_STORAGETHREAD_H
#define ACUTERECORDER_STORAGETHREAD_H


#include <QObject>
#include <QSize>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>

class QImage;

class RecorderStorageWorker : public QObject
{

Q_OBJECT

  QSize size_;
  int fps_;
  QString output_;

  int expectedBytesPerLine_;

  QMutex mutex_;
  QWaitCondition notEmptyCondition_;

  QQueue< QImage * > queue_;
  volatile bool running_ ;

  /**
   * Pops an image from the queue. This method blocks the thread
   * until an image is found or the thread should end.
   *
   * If this second scenario occurs this method returns false.
   *
   * @param image the popped image.
   * @return whether the thread should continue.
   */
  bool popElement( QImage *& image );

public:

  /**
   * Creates the storage worker.
   * @param size the size of each frame.
   * @param fps the FPS of the video.
   * @param output the output path of the video.
   */
  RecorderStorageWorker( const QSize& size , int fps , QString output );

  /**
   * Sends a frame to the storage.
   * @param image the frame.
   */
  void push( QImage *image );

public slots:

  /**
   * Starts the worker.
   * This method does nothing if the worker is already running.
   */
  void start( );

  /**
   * Stops the worker.
   * This method does nothing if the worker is not running.
   */
  void stop( );

signals:

  /**
   * Notifies the termination of the worker.
   */
  void finished( );

  /**
   * Notifies a change in the buffer of the worker.
   * @param size the size of the buffer.
   */
  void fileQueueSizeChanged( int size );

};


#endif //ACUTERECORDER_STORAGETHREAD_H
