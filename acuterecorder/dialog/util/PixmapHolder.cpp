//
// Created by Gael Rial Costas on 08/11/2021.
//

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