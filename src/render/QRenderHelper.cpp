//
// Created by Gael Rial Costas on 2/9/21.
//

#include <QPainter>
#include <QScreen>
#include <iostream>
#include "QRenderHelper.h"
#include "../data/ViewportI.h"

QRenderHelper::QRenderHelper( QWidget *widget ) : widget_( widget ) ,
                                                  screen_( nullptr )
{ }

QRenderHelper::QRenderHelper( QScreen *screen ) : screen_( screen ) ,
                                                  widget_( nullptr )
{ }

QImage *QRenderHelper::render( const QSize& size , const ViewportD& viewport )
{
  return screen_ == nullptr
         ? renderWidget( size , viewport )
         : renderScreen( size , viewport );
}

QImage *
QRenderHelper::renderWidget( const QSize& size , const ViewportD& relative )
{
  ViewportI viewport( relative , widget_->size( ));

  auto *image = new QImage( size , QImage::Format_RGB888 );
  QPainter painter( image );

  // This scales the widget to fit the image.
  painter.scale(( double ) size.width( ) / viewport.width ,
                ( double ) size.height( ) / viewport.height );

  // Make the origin the coordinate 0,0.
  painter.translate( -viewport.origin( ));

  // Renders and sends the image to the storage thread.
  widget_->render( &painter );
  return image;
}

QImage *
QRenderHelper::renderScreen( const QSize& size , const ViewportD& relative )
{

  // Using grabWindow we can use the viewport directly to get the desired area.
  ViewportI v( relative , screen_->size( ));
  auto pixmap = screen_->grabWindow( 0 , v.x , v.y , v.width , v.height );

  // Now we have to scale the pixmap to the desired size.
  pixmap = pixmap.scaled( size.width( ) , size.height( ) ,
                          Qt::IgnoreAspectRatio ,
                          Qt::SmoothTransformation );

  // Finally, convert the data to an image pointer.
  // This may seem a bad code, but Qt does its magic under the hood.
  return new QImage( pixmap.toImage( )
                       .convertToFormat( QImage::Format_RGB888 ));
}

QWidget *QRenderHelper::widget( ) const
{
  return widget_;
}

QScreen *QRenderHelper::screen( ) const
{
  return screen_;
}
