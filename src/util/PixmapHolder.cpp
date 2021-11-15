//
// Created by gaelr on 08/11/2021.
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
  setPixmap( getScaledPixmap( ));
}

void PixmapHolder::resizeEvent( QResizeEvent *resizeEvent )
{
  if ( pixmap_.isNull( )) return;
  setPixmap( getScaledPixmap( ));
}
