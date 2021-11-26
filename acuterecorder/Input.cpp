//
// Created by gaelr on 18/11/2021.
//

#include "Input.h"

#include <QSize>
#include <QWidget>
#include <QScreen>
#include <QPainter>

Input::Input( ) :
  widget_( nullptr ) ,
  screen_( nullptr )
{

}

Input::Input( QWidget *widget ) :
  widget_( widget ) ,
  screen_( nullptr )
{
}

Input::Input( QScreen *screen ) :
  widget_( nullptr ) ,
  screen_( screen )
{
}

InputType Input::getType( ) const
{
  if ( !widget_ && !screen_ ) return InputType::INVALID;
  return widget_ == nullptr ? InputType::SCREEN : InputType::WIDGET;
}

bool Input::isWidget( ) const
{
  return widget_ != nullptr;
}

bool Input::isScreen( ) const
{
  return screen_ != nullptr;
}

QImage * Input::render( const QRectF& inputArea , const QSize& outputSize ) const
{
  if ( widget_ == nullptr && screen_ == nullptr )
  {
    throw std::logic_error( "Input is invalid: it has no widget or screen." );
  }

  QSize inputSize = widget_ == nullptr ? screen_->size( ) : widget_->size( );
  QRect viewport{
    static_cast<int>(inputArea.x( ) * inputSize.width( )) ,
    static_cast<int>(inputArea.y( ) * inputSize.height( )) ,
    static_cast<int>(inputArea.width( ) * inputSize.width( )) ,
    static_cast<int>(inputArea.height( ) * inputSize.height( ))
  };

  if ( widget_ != nullptr )
  {
    auto image = new QImage( outputSize , QImage::Format_RGB888 );
    QPainter painter( image );

    // This scales the widget to fit the image.
    painter.scale(
      static_cast<double>(outputSize.width( )) / viewport.width( ) ,
      static_cast<double >(outputSize.height( )) / viewport.height( )
    );

    // Make the origin the coordinate 0,0.
    painter.translate( -viewport.x( ) , -viewport.y( ));

    // Renders and sends the image to the storage thread.
    widget_->render( &painter );
    return image;
  }
  else
  {
    auto pixmap = screen_->grabWindow(
      0 ,
      viewport.x( ) ,
      viewport.y( ) ,
      viewport.width( ) ,
      viewport.height( )
    );

    // Now we have to scale the pixmap to the desired size.
    pixmap = pixmap.scaled(
      outputSize.width( ) ,
      outputSize.height( ) ,
      Qt::IgnoreAspectRatio ,
      Qt::SmoothTransformation
    );

    // Finally, convert the data to an image pointer.
    // This may seem a bad code, but Qt does its magic under the hood.
    return new QImage( pixmap.toImage( )
                         .convertToFormat( QImage::Format_RGB888 ));
  }
}

QSize Input::getSize( ) const
{
  if ( widget_ == nullptr && screen_ == nullptr )
  {
    throw std::logic_error( "Input is invalid: it has no widget or screen." );
  }

  return widget_ == nullptr ? screen_->size() : widget_->size();
}
