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

  RecorderStorageWorker( const QSize& size , int fps , QString output );

  void push( QImage *image );

public slots:

  void start( );

  void stop( );

signals:

  void finished( );

  void fileQueueSizeChanged( int size );

};


#endif //ACUTERECORDER_STORAGETHREAD_H
