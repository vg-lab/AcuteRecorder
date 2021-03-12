//
// Created by gaeqs on 8/3/21.
//

#ifndef QTRECORDER_WIDGETRENDERTHREAD_H
#define QTRECORDER_WIDGETRENDERTHREAD_H


#include <QSize>
#include <QWidget>
#include <QTimer>
#include <chrono>
#include "VideoStorageThread.h"

typedef std::chrono::time_point< std::chrono::system_clock , std::chrono::nanoseconds > TimeStamp;

/**
 * This thread renders the given widget at the given framerate and sends
 * the raw result to a VideoStorageThread.
 */
class WidgetRenderThread : public AbstractRendererThread
{

  VideoStorageThread storageThread_;
  QWidget *widget_;
  QTimer *timer_{};

  TimeStamp start_;
  TimeStamp lastFrame_;
  std::chrono::microseconds delayPerFrame_;
  int imagesRendered_;

  void run( ) override;

  /**
   * Renders the widget and sends the raw image to the storage thread.
   */
  void render( );

public:

  /**
   * Creates a render thread.
   *
   * This constructor also creates a VideoStorageThread.
   *
   * @param fps the amount of images per second to render.
   * @param size the dimensions of the images to render.
   * @param widget the widget to render.
   */
  WidgetRenderThread( const QSize& size , int fps , QWidget *widget );

  /**
   * Returns the VideoStorageThread inside this render thread.
   * @return the VideoStorageThread.
   */
  VideoStorageThread *storeManager( );

  bool start( ) override;

  void stop( ) override;

  bool setFPS( int fps ) override;

  bool setSize( const QSize& size ) override;
};


#endif //QTRECORDER_WIDGETRENDERTHREAD_H
