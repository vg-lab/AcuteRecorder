/*
 * Copyright (c) 2021-2024 VG-Lab/URJC.
 *
 * Authors: Gael Rial Costas <gael.rial.costas@urjc.es>
 *
 * This file is part of AcuteRecorder <https://github.com/vg-lab/AcuteRecorder>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

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

QWidget *Input::getWidget( ) const
{
  return widget_;
}

QScreen *Input::getScreen( ) const
{
  return screen_;
}

std::shared_ptr< QImage >
Input::render( const QRectF& inputArea , const QSize& outputSize ) const
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
    auto image = std::make_shared< QImage >(
      outputSize , QImage::Format_RGB888
    );
    QPainter painter( image.get( ));

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

    return std::make_shared< QImage >(
      pixmap.toImage( ).convertToFormat( QImage::Format_RGB888 )
    );
  }
}

QSize Input::getSize( ) const
{
  if ( widget_ == nullptr && screen_ == nullptr )
  {
    throw std::logic_error( "Input is invalid: it has no widget or screen." );
  }

  return widget_ == nullptr ? screen_->size( ) : widget_->size( );
}
