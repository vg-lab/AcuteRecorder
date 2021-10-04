//
// Created by Gael Rial Costas on 6/3/21.
//

#ifndef QTRECORDER_SELECTIONAREA_H
#define QTRECORDER_SELECTIONAREA_H

#include <QRubberBand>
#include <QLabel>
#include "../data/RecorderGeneralData.h"

class SelectionArea : public QLabel
{

Q_OBJECT

  RecorderGeneralData *data_;
  QRubberBand *band_;
  QPoint origin_;
  bool dragging_;

  QTimer *resizeCheckTimer_;

  void onTimerTick( );

  void renderImage( );

  void checkRenderArea( );

protected:

  void mousePressEvent( QMouseEvent *event ) override;

  void mouseMoveEvent( QMouseEvent *event ) override;

  void mouseReleaseEvent( QMouseEvent *event ) override;

  void resizeEvent( QResizeEvent *event ) override;

public:

  SelectionArea( QWidget *parent , RecorderGeneralData *data );

  void refreshSelectionMode( );

  QPoint toPixmapPoint( const QPoint& localPoint );

  QPoint fromPixmapPoint( const QPoint& localPoint );

};


#endif //QTRECORDER_SELECTIONAREA_H
