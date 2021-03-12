//
// Created by gaeqs on 8/3/21.
//

#ifndef QTRECORDER_VIDEOSTORAGETHREAD_H
#define QTRECORDER_VIDEOSTORAGETHREAD_H


#include <QQueue>
#include <QImage>
#include <QMutex>
#include <QWaitCondition>
#include <QFuture>
#include "AbstractRendererThread.h"

/**
 * This thread executes a FFMPEG command that converts the given raw images
 * into a mp4 video.
 */
class VideoStorageThread : public AbstractRendererThread
{

  QQueue< QImage * > queue_;
  FILE *file_;

  QMutex mutex_;
  QWaitCondition notEmptyCondition_;
  std::string output_;

  QFuture< void > future_;

  volatile int filesInQueue_;

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

  void run( ) override;

public:

  /**
   * Creates a new storage thread.
   * @param size the size of the video to store.
   * @param fps the framerate of the video to store.
   */
  VideoStorageThread( const QSize& size , int fps );

  /**
   * Waits for this thread to finish.
   */
  void join( );

  /**
   * Send an image to this thread.
   * @param image the image.
   */
  void push( QImage *image );

  /**
   * Returns the amount of images this thread has in the queue.
   * @return the amount of images in the queue.
   */
  int filesInQueue( ) const;

  /**
   * Returns the output path of the video to render.
   * @return the output path of the video.
   */
  std::string output( ) const;

  /**
   * Sets the output path of the video to render.
   *
   * This method can only be performed when the thread is stopped!
   *
   * @param output the output path of the video.
   * @return whether this operation was successful.
   */
  bool setOutput( const std::string& output );

  bool start( ) override;
};


#endif //QTRECORDER_VIDEOSTORAGETHREAD_H
