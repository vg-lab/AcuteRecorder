//
// Created by gaeqs on 6/3/21.
//

#include <iostream>
#include "MyRubberWindow.h"

void MyRubberWindow::mousePressEvent( QMouseEvent *event )
{
  origin_ = event->pos( );

  if ( band_ == nullptr )
  {
    band_ = new QRubberBand( QRubberBand::Rectangle , this );
  }

  band_->setGeometry( QRect( origin_ , QSize( )));
  band_->show( );
}

void MyRubberWindow::mouseMoveEvent( QMouseEvent *event )
{
  band_->setGeometry( QRect( origin_ , event->pos( )).normalized( ));
}

void MyRubberWindow::mouseReleaseEvent( QMouseEvent *event )
{
}

MyRubberWindow::MyRubberWindow( QImage& image ) : band_( nullptr )
{

  QPixmap map;
  map.convertFromImage( image , Qt::ColorOnly );

  setPixmap( map );
}
