//
// Created by gaelr on 15/11/2021.
//

#include "RecorderGeneralData.h"

QWidget *RecorderGeneralData::getFinalWidgetToRender( ) const
{
  return selectionMode == WIDGET ? selectedWidget : renderingWidget;
}

QRenderHelper RecorderGeneralData::getFinalRenderHelper( ) const
{
  return screen == nullptr
         ? QRenderHelper( getFinalWidgetToRender( ))
         : QRenderHelper( screen );
}

QSize RecorderGeneralData::getFinalSourceSize( ) const
{
  switch ( selectionMode )
  {
    case WIDGET:
      return selectedWidget->size( );
    case AREA:
    case FULL:
    default:
      return screen == nullptr ? renderingWidget->size( ) : screen->size( );
  }
}

QSize RecorderGeneralData::getFinalDestinationSize( ) const
{
  switch ( destinationMode )
  {
    case FIXED:
      return destinationSize;
    case SCALED:
    default:
      auto s = getFinalSourceSize( );
      return {
        static_cast<int>(( s.width( ) * destinationScale.width( ))) ,
        static_cast<int>(( s.height( ) * destinationScale.height( )))
      };
  }
}

QRectF RecorderGeneralData::getFinalSourceViewport( ) const
{
  switch ( selectionMode )
  {
    case AREA:
      return sourceViewport;
    case WIDGET:
    case FULL:
    default:
      return { 0 , 0 , 1 , 1 };
  }
}