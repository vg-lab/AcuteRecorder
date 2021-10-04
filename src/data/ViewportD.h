//
// Created by Gael Rial Costas on 16/8/21.
//

#ifndef QTRECORDER_VIEWPORTD_H
#define QTRECORDER_VIEWPORTD_H

struct ViewportD
{

  double x;
  double y;
  double width;
  double height;

  ViewportD( ) : x( 0 ) , y( 0 ) , width( 0 ) , height( 0 )
  {
  }

  ViewportD( double x , double y , double width , double height )
    : x( x ) , y( y ) , width( width ) , height( height )
  {
  }

  friend std::ostream& operator<<( std::ostream& os , const ViewportD& dt )
  {
    os << "[" << dt.x << ", " << dt.y << "] ("
       << dt.width << ", " << dt.height << ")";
    return os;
  }

};

#endif //QTRECORDER_VIEWPORTD_H
