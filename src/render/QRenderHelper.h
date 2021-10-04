//
// Created by Gael Rial Costas on 2/9/21.
//

#ifndef QTRECORDER_QRENDERHELPER_H
#define QTRECORDER_QRENDERHELPER_H


#include <QWidget>
#include "../data/ViewportD.h"

/**
 * Helper class used to grab QImages from a widget or a screen.
 */
class QRenderHelper
{

  QWidget *widget_;
  QScreen *screen_;

  QImage *renderWidget( const QSize& size , const ViewportD& relative );

  QImage *renderScreen( const QSize& size , const ViewportD& relative );

public:

  /**
   * Creates the helper. The helper will render the given widget.
   * @param widget the widget to render.
   */
  QRenderHelper( QWidget *widget );

  /**
   * Creates the helper. The helper will render the given screen.
   * @param screen the screen to render.
   */
  QRenderHelper( QScreen *screen );

  /**
   * Renders the widget or screen stored in this helper.
   * @param size the size of the QImage to generate.
   * @param viewport the relative viewport for the source image.
   * @return
   */
  QImage *render( const QSize& size , const ViewportD& viewport );

  /**
   * Returns the widget inside the helper or null if the helper uses a screen.
   * @return the widget or null.
   */
  QWidget *widget( ) const;

  /**
     * Returns the screen inside the helper or null if the helper uses a widget.
     * @return the screen or null.
     */
  QScreen *screen( ) const;

};


#endif //QTRECORDER_QRENDERHELPER_H
