//
// Created by gaeqs on 6/3/21.
//

#ifndef QTRECORDER_MYRUBBERWINDOW_H
#define QTRECORDER_MYRUBBERWINDOW_H


#include <QWidget>
#include <QRubberBand>
#include <QMouseEvent>
#include <QLabel>

class MyRubberWindow : public QLabel
{

Q_OBJECT

  QRubberBand *band_;
  QPoint origin_;

protected:

  void mousePressEvent( QMouseEvent *event ) override;

  void mouseMoveEvent( QMouseEvent *event ) override;

  void mouseReleaseEvent( QMouseEvent *event ) override;

public:

  explicit MyRubberWindow( QImage& image );

};


#endif //QTRECORDER_MYRUBBERWINDOW_H
