//
// Created by Gael Rial Costas on 16/8/21.
//

#ifndef QTRECORDER_VIEWPORTI_H
#define QTRECORDER_VIEWPORTI_H

#include "ViewportD.h"

struct ViewportI
{

  int x;
  int y;
  int width;
  int height;

  ViewportI( ) : x( 0 ) , y( 0 ) , width( 0 ) , height( 0 )
  {
  }

  ViewportI( int x , int y , int width , int height )
    : x( x ) , y( y ) , width( width ) , height( height )
  {
  }

  ViewportI( ViewportD relative , const QSize& size ) :
    x( relative.x * size.width( )) ,
    y( relative.y * size.height( )) ,
    width( relative.width * size.width( )) ,
    height( relative.height * size.height( ))
  {
  }


  QSize size( )
  {
    return { width , height };
  }

  QPoint origin( )
  {
    return { x , y };
  }

  ViewportD relativize( const QSize& size )
  {
    double w = size.width( );
    double h = size.height( );
    return { x / w , y / h , width / w , height / h };
  }

  friend std::ostream& operator<<( std::ostream& os , const ViewportI& dt )
  {
    os << "[" << dt.x << ", " << dt.y << "] ("
       << dt.width << ", " << dt.height << ")";
    return os;
  }

};


#endif //QTRECORDER_VIEWPORTI_H
