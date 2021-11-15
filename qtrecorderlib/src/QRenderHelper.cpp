//
// Created by Gael Rial Costas on 2/9/21.
//

#include "../include/QRenderHelper.h"

#include <iostream>

#include <QPainter>
#include <QScreen>
#include <QDebug>

QRenderHelper::QRenderHelper( QWidget *widget ) : widget_( widget ) ,
                                                  screen_( nullptr )
{ }

QRenderHelper::QRenderHelper( QScreen *screen ) : screen_( screen ) ,
                                                  widget_( nullptr )
{ }

QImage *QRenderHelper::render( const QSize& size , const QRectF& viewport )
{
  return screen_ == nullptr
         ? renderWidget( size , viewport )
         : renderScreen( size , viewport );
}

QImage *
QRenderHelper::renderWidget( const QSize& size , const QRectF& relative )
{

  QSize ws = widget_->size( );
  QRect viewport{
    static_cast<int>(relative.x( ) * ws.width( )) ,
    static_cast<int>(relative.y( ) * ws.height( )) ,
    static_cast<int>(relative.width( ) * ws.width( )) ,
    static_cast<int>(relative.height( ) * ws.height( ))
  };

  auto *image = new QImage( size , QImage::Format_RGB888 );
  QPainter painter( image );

  // This scales the widget to fit the image.
  painter.scale( static_cast<double>(size.width( )) / viewport.width( ) ,
                 static_cast<double >(size.height( )) / viewport.height( ));

  // Make the origin the coordinate 0,0.
  painter.translate( -viewport.x( ) , -viewport.y( ));

  // Renders and sends the image to the storage thread.
  widget_->render( &painter );
  return image;
}

QImage *
QRenderHelper::renderScreen( const QSize& size , const QRectF& relative )
{

  // Using grabWindow we can use the viewport directly to get the desired area.
  QSize ss = screen_->size( );
  QRect viewport{
    static_cast<int>(relative.x( ) * ss.width( )) ,
    static_cast<int>(relative.y( ) * ss.height( )) ,
    static_cast<int>(relative.width( ) * ss.width( )) ,
    static_cast<int>(relative.height( ) * ss.height( ))
  };

  auto pixmap = screen_->grabWindow(
    0 ,
    viewport.x( ) ,
    viewport.y( ) ,
    viewport.width( ) ,
    viewport.height( )
  );

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
