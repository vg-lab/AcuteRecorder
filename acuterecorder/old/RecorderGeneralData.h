//
// Created by Gael Rial Costas on 16/8/21.
//

#ifndef QTRECORDER_RECORDERGENERALDATA_H
#define QTRECORDER_RECORDERGENERALDATA_H

#include <QWidget>
#include <QSize>
#include <QScreen>
#include <iostream>
#include <memory>

#include "AbstractRendererThread.h"
#include "QRenderHelper.h"

class WidgetRenderThread;

enum class SelectionMode
{
  FULL = 0, AREA , WIDGET
};

enum class DestinationMode
{
  SCALED = 0, FIXED
};

/**
 * Represents the configuration of the recorder.
 *
 * Instances of this struct are also used to manage the
 * initialization / stop of a recording.
 */
struct RecorderGeneralData
{
  /**
   * The widget of this recorder.
   */
  QWidget *recorderWidget = nullptr;

  /**
   * The widget to render.
   */
  QWidget *renderingWidget = nullptr;

  /**
   * The screen to render. If not null, renderingWidget will be discarded.
   */
  QScreen *screen = nullptr;

  /**
   * The source viewport selection mode. It may be full, widget or area.
   */
  SelectionMode selectionMode = SelectionMode::FULL;

  /**
   * The selected widget to render. This must be a child of renderingWidget.
   */
  QWidget *selectedWidget = nullptr;

  /**
   * The source viewport, normalized.
   */
  QRectF sourceViewport = QRectF( 0 , 0 , 1 , 1 );

  /**
   * The destination mode. It may be fixed or scaled.
   */
  DestinationMode destinationMode = DestinationMode::SCALED;

  /**
   * The destination video size. Used in fixed mode.
   */
  QSize destinationSize = QSize( 1920 , 1080 );

  /**
   * The destination video scale. Used in scaled mode.
   * The final video size will be sourceViewport.size() * destinationScale.
   */
  QSizeF destinationScale = QSizeF( 1.0f , 1.0f );

  /**
   * The FPS of the final video.
   */
  int fps = 60;

  /**
   * The output path of the final video.
   */
  QString output = "output.mp4";

  /**
   * The rendering thread.
   */
  std::shared_ptr<WidgetRenderThread> thread = nullptr;

  /**
   * Returns whether this RecorderGeneralData is being
   * used to record.
   * @return whether a recorder is using this RecorderGeneralData.
   */
  bool isRecording( ) const;

  /**
   * Returns the widget that the thread has to render.
   * This method returns an unpredictable value if the
   * selected source is not a widget.
   * @return the widget to render.
   */
  QWidget *getFinalWidgetToRender( ) const;

  /**
   * Returns the QRenderHelper to used by the render thread.
   *
   * This QRenderHelper's configuration is created using this general data.
   *
   * @return the render helper.
   */
  QRenderHelper getFinalRenderHelper( ) const;

  /**
   * Returns the size of the final source.
   * This may be the selected widget's size or the screen's size.
   * @return the size.
   */
  QSize getFinalSourceSize( ) const;

  /**
   * Returns the source viewport to use by the recorder.
   * @return the source viewport.
   */
  QRectF getFinalSourceViewport( ) const;

  /**
   * Returns the final size of the output.
   * @return the size of the output.
   */
  QSize getFinalDestinationSize( ) const;
};

#endif //QTRECORDER_RECORDERGENERALDATA_H
