//
// Created by Gael Rial Costas on 16/8/21.
//

#ifndef QTRECORDER_RECORDERGENERALDATA_H
#define QTRECORDER_RECORDERGENERALDATA_H

#include <QWidget>
#include <QSize>
#include <QScreen>
#include <iostream>

#include "AbstractRendererThread.h"
#include "QRenderHelper.h"

class WidgetRenderThread;

enum SelectionMode
{
  FULL , AREA , WIDGET
};

enum DestinationMode
{
  SCALED , FIXED
};

struct RecorderGeneralData
{

  QWidget *recorderWidget = nullptr;
  QWidget *renderingWidget = nullptr;
  QScreen *screen = nullptr;

  SelectionMode selectionMode = FULL;
  QWidget *selectedWidget = nullptr;
  QRectF sourceViewport = QRectF( 0 , 0 , 1 , 1 );

  DestinationMode destinationMode = SCALED;
  QSize destinationSize = QSize( 1920 , 1080 );
  QSizeF destinationScale = QSizeF( 1.0f , 1.0f );

  int fps = 60;
  QString output = "output.mp4";

  WidgetRenderThread *thread = nullptr;

  /**
   * Returns the widget that the thread has to render.
   * This method returns an unpredictable value if the
   * selected source is not a widget.
   * @return the widget to render.
   */
  [[nodiscard]] QWidget *getFinalWidgetToRender( ) const;

  /**
   * Returns the QRenderHelper to used by the render thread.
   *
   * This QRenderHelper's configuration is created using this general data.
   *
   * @return the render helper.
   */
  [[nodiscard]] QRenderHelper getFinalRenderHelper( ) const;

  /**
   * Returns the size of the final source.
   * This may be the selected widget's size or the screen's size.
   * @return the size.
   */
  [[nodiscard]] QSize getFinalSourceSize( ) const;

  /**
   * Returns the source viewport to use by the recorder.
   * @return the source viewport.
   */
  [[nodiscard]] QRectF getFinalSourceViewport( ) const;

  /**
   * Returns the final size of the output.
   * @return the size of the output.
   */
  [[nodiscard]] QSize getFinalDestinationSize( ) const;
};

#endif //QTRECORDER_RECORDERGENERALDATA_H
