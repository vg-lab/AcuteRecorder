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

#include "PixmapHolder.h"

PixmapHolder::PixmapHolder( QWidget *parent ) :
  QLabel( parent )
{
  setMinimumSize( 1 , 1 );
  setScaledContents( false );
}

QPixmap PixmapHolder::getScaledPixmap( ) const
{
  return pixmap_.scaled(
    size( ) ,
    Qt::KeepAspectRatio ,
    Qt::SmoothTransformation
  );
}

void PixmapHolder::setHolderPixmap( const QPixmap& pixmap )
{
  pixmap_ = pixmap;
  QPixmap scaled = getScaledPixmap();
  width_ = scaled.width();
  height_ = scaled.height();
  setPixmap( scaled );
}

void PixmapHolder::resizeEvent( QResizeEvent * )
{
  if ( pixmap_.isNull( )) return;
  QPixmap scaled = getScaledPixmap();
  width_ = scaled.width();
  height_ = scaled.height();
  setPixmap( scaled );
}

int PixmapHolder::getWidth( ) const
{
  return width_;
}

int PixmapHolder::getHeight( ) const
{
  return height_;
}