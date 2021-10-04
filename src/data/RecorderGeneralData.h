//
// Created by Gael Rial Costas on 16/8/21.
//

#ifndef QTRECORDER_RECORDERGENERALDATA_H
#define QTRECORDER_RECORDERGENERALDATA_H

#include <QWidget>
#include <QSize>
#include <QScreen>
#include <iostream>
#include "../render/AbstractRendererThread.h"
#include "ViewportI.h"
#include "../render/QRenderHelper.h"

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
  ViewportI sourceViewport;

  DestinationMode destinationMode = SCALED;
  QSize destinationSize = QSize( 1920 , 1080 );
  QSizeF destinationScale = QSizeF( 1.0f , 1.0f );

  int fps = 60;
  QString output = "output.mp4";

  WidgetRenderThread *thread = nullptr;

  QWidget *getFinalWidgetToRender( )
  {
    if ( selectionMode == WIDGET )
    {
      return selectedWidget;
    }

    return renderingWidget;
  }

  QRenderHelper getFinalRenderHelper( )
  {
    if ( screen != nullptr )
    {
      return { screen };
    }
    return { getFinalWidgetToRender( ) };
  }

  ViewportI getFinalSourceViewport( )
  {

    switch ( selectionMode )
    {
      case FULL:
        if ( screen != nullptr )
        {
          auto s = screen->size( );
          return { 0 , 0 , s.width( ) , s.height( ) };
        }
        return { 0 , 0 ,
                 renderingWidget->width( ) ,
                 renderingWidget->height( ) };
      case WIDGET:
        return { 0 , 0 ,
                 selectedWidget->width( ) ,
                 selectedWidget->height( ) };
      case AREA:
      default:
        return sourceViewport;
    }
  }

  ViewportD getFinalRelativeViewport( )
  {
    auto size = screen == nullptr
                ? getFinalWidgetToRender( )->size( )
                : screen->size( );
    return getFinalSourceViewport( ).relativize( size );
  }

  QSize getFinalDestinationSize( )
  {
    switch ( destinationMode )
    {
      case FIXED:
        return destinationSize;
      case SCALED:
      default:
        auto s = getFinalSourceViewport( ).size( );
        return { ( int ) ( s.width( ) * destinationScale.width( )) ,
                 ( int ) ( s.height( ) * destinationScale.height( )) };
    }
  }

};

#endif //QTRECORDER_RECORDERGENERALDATA_H
