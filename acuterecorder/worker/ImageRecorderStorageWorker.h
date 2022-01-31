//
// Created by Gael Rial Costas on 18/11/2021.
//

#ifndef ACUTERECORDER_QTSTORAGETHREAD_H
#define ACUTERECORDER_QTSTORAGETHREAD_H


#include <QObject>
#include <QSize>
#include <QDir>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QThread>

#include "RecorderStorageWorker.h"

class QImage;

/**
 * This storage workers saves the frames in separate PNG files inside
 * a folder.
 */
class ImageRecorderStorageWorker : public RecorderStorageWorker
{

Q_OBJECT

  QDir output_;

  QMutex mutex_;
  QWaitCondition notEmptyCondition_;

  QQueue< QImage * > queue_;
  volatile bool running_;

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

protected:

  void run( ) override;

public:

  /**
   * Creates the storage worker.
   * @param output the path of the output folder.
   */
  ImageRecorderStorageWorker( QObject *object , const QString &output );
  virtual ~ImageRecorderStorageWorker() {};

  virtual void push( QImage *image ) override;

public slots:

  virtual void stop( ) override;

};


#endif //ACUTERECORDER_QTSTORAGETHREAD_H
