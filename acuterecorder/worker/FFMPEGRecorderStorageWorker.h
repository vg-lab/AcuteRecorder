//
// Created by Gael Rial Costas on 18/11/2021.
//

#ifndef ACUTERECORDER_FFMPEGSTORAGETHREAD_H
#define ACUTERECORDER_FFMPEGSTORAGETHREAD_H


#include <QObject>
#include <QSize>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QThread>

#include "RecorderStorageWorker.h"

class QImage;

/**
 * This worker saves the frames in a .mp4 video using FFMPEG.
 */
class FFMPEGRecorderStorageWorker : public RecorderStorageWorker
{

Q_OBJECT

  QSize size_;
  int fps_;
  QString output_;

  qint64 expectedBytesPerLine_;

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
   * @param size the size of each frame.
   * @param fps the FPS of the video.
   * @param output the output path of the video.
   */
  FFMPEGRecorderStorageWorker( QObject *object ,
                               const QSize& size , int fps , QString output );

  virtual void push( QImage *image ) override;

public slots:

  virtual void stop( ) override;

};


#endif //ACUTERECORDER_FFMPEGSTORAGETHREAD_H
