//
// Created by gaeqs on 12/3/21.
//

#ifndef QTRECORDER_ABSTRACTRENDERERTHREAD_H
#define QTRECORDER_ABSTRACTRENDERERTHREAD_H


#include <QSize>
#include <QFuture>

/**
 * Base class for threads in the render pipeline.
 */
class AbstractRendererThread
{

protected:

  QSize size_;
  int fps_;

  QFuture< void > future_;

  volatile bool running_ , finished_;

  /**
   * This method handles all this storage thread logic.
   */
  virtual void run( ) = 0;

public:

  /**
   * Creates the thread.
   * @param size the dimensions of the video.
   * @param fps  the framerate of the video.
   */
  AbstractRendererThread( const QSize& size , int fps );

  /**
   * Starts the thread. If this thread is running this method does nothing.
   *
   * @return whether the thread has started. This method returns false
   * if the thread is already running.
   */
  virtual bool start( );

  /**
   * Signals the thread that it must stop.
   * This method DOESN'T stop the thread immediately!
   * Use join( ) after this method if you need to wait for
   * the thread to stop.
   */
  virtual void stop( );

  /**
   * Returns whether this thread is running.
   * @return whether this thread is running.
   */
  bool isThreadRunning( ) const;

  /**
   * Waits for this thread to finish.
   */
  void join( );

  /**
   * Returns the framerate of the resulted video.
   * @return the framerate of the resulted video.
   */
  int FPS( ) const;

  /**
   * Sets the framerate of the video.
   *
   * This method can only be performed when the thread is stopped!
   *
   * @param fps the framerate.
   * @return whether this operation was successful.
   */
  virtual bool setFPS( int fps );

  /**
   * Returns the dimensions of the resulted video.
   * @return the dimensions of the resulted video.
   */
  QSize size( ) const;

  /**
   * Sets the dimensions of the video.
   *
   * This method can only be performed when the thread is stopped!
   *
   * @param size the dimensions.
   * @return whether this operation was sucessful.
   */
  virtual bool setSize( const QSize& size );
};


#endif //QTRECORDER_ABSTRACTRENDERERTHREAD_H
