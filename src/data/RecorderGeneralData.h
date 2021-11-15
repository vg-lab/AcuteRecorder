//
// Created by Gael Rial Costas on 16/8/21.
//

#ifndef QTRECORDER_RECORDERGENERALDATA_H
#define QTRECORDER_RECORDERGENERALDATA_H

#include <QWidget>
#include <QSize>
#include <QScreen>
#include <iostream>

#include <render/AbstractRendererThread.h>
#include <render/QRenderHelper.h>

class WidgetRenderThread;

enum SelectionMode
{
  FULL , AREA , WIDGET
};

enum DestinationMode
{
  SCALED , FIXED
};

struct RecorderGeneralData
{

  QWidget *recorderWidget = nullptr;
  QWidget *renderingWidget = nullptr;
  QScreen *screen = nullptr;

  SelectionMode selectionMode = FULL;
  QWidget *selectedWidget = nullptr;
  QRectF sourceViewport;

  DestinationMode destinationMode = SCALED;
  QSize destinationSize = QSize( 1920 , 1080 );
  QSizeF destinationScale = QSizeF( 1.0f , 1.0f );

  int fps = 60;
  QString output = "output.mp4";

  WidgetRenderThread *thread = nullptr;

  [[nodiscard]] QWidget *getFinalWidgetToRender( ) const
  {
    if ( selectionMode == WIDGET )
    {
      return selectedWidget;
    }

    return renderingWidget;
  }

  [[nodiscard]] QRenderHelper getFinalRenderHelper( ) const
  {
    if ( screen != nullptr )
    {
      return QRenderHelper( screen );
    }
    return QRenderHelper( getFinalWidgetToRender( ));
  }

  [[nodiscard]] QRect getFinalSourceViewport( ) const
  {
    switch ( selectionMode )
    {
      case FULL:
        if ( screen != nullptr )
        {
          auto s = screen->size( );
          return {
            0 ,
            0 ,
            s.width( ) ,
            s.height( )
          };
        }
        return {
          0 ,
          0 ,
          renderingWidget->width( ) ,
          renderingWidget->height( )
        };
      case WIDGET:
        return {
          0 ,
          0 ,
          selectedWidget->width( ) ,
          selectedWidget->height( )
        };
      case AREA:
      default:
        if ( screen != nullptr )
        {
          QSize size = screen->size( );
          return {
            static_cast<int>(sourceViewport.x( ) * size.width( )) ,
            static_cast<int>(sourceViewport.y( ) * size.height( )) ,
            static_cast<int>(sourceViewport.width( ) * size.width( )) ,
            static_cast<int>(sourceViewport.height( ) * size.height( ))
          };
        }
        QSize size = renderingWidget->size( );
        return {
          static_cast<int>(sourceViewport.x( ) * size.width( )) ,
          static_cast<int>(sourceViewport.y( ) * size.height( )) ,
          static_cast<int>(sourceViewport.width( ) * size.width( )) ,
          static_cast<int>(sourceViewport.height( ) * size.height( ))
        };
    }
  }

  [[nodiscard]] QRectF getFinalRelativeViewport( ) const
  {
    QSizeF size = screen == nullptr
                  ? getFinalWidgetToRender( )->size( )
                  : screen->size( );
    QRectF fsv = getFinalSourceViewport( );
    return {
      fsv.x( ) / size.width( ) ,
      fsv.y( ) / size.height( ) ,
      fsv.width( ) / size.width( ) ,
      fsv.height( ) / size.height( )
    };
  }

  [[nodiscard]] QSize getFinalDestinationSize( ) const
  {
    switch ( destinationMode )
    {
      case FIXED:
        return destinationSize;
      case SCALED:
      default:
        auto s = getFinalSourceViewport( ).size( );
        return {
          static_cast<int>(( s.width( ) * destinationScale.width( ))) ,
          static_cast<int>(( s.height( ) * destinationScale.height( )))
        };
    }
  }

};

#endif //QTRECORDER_RECORDERGENERALDATA_H
