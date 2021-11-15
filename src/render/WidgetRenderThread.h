//
// Created by Gael Rial Costas on 8/3/21.
//

#ifndef QTRECORDER_WIDGETRENDERTHREAD_H
#define QTRECORDER_WIDGETRENDERTHREAD_H

#include "VideoStorageThread.h"
#include "QRenderHelper.h"

#include <chrono>

#include <QSize>
#include <QWidget>
#include <QTimer>

#include <data/RecorderGeneralData.h>

typedef std::chrono::time_point< std::chrono::system_clock , std::chrono::nanoseconds > TimeStamp;

/**
 * This thread renders the given widget at the given framerate and sends
 * the raw result to a VideoStorageThread.
 */
class WidgetRenderThread : public AbstractRendererThread
{

  QWidget *recorderWidget_;

  VideoStorageThread storageThread_;
  QRenderHelper helper_;
  QTimer *timer_;

  TimeStamp start_;
  int imagesRendered_;
  QRectF relativeViewport_;

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
   * @param data the data this recorder will get the data from.
   */
  WidgetRenderThread( RecorderGeneralData *data );

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
