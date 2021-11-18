//
// Created by gaelr on 15/11/2021.
//

#include "RecorderGeneralData.h"

bool RecorderGeneralData::isRecording( ) const
{
  return thread != nullptr;
}

QWidget *RecorderGeneralData::getFinalWidgetToRender( ) const
{
  return selectionMode == SelectionMode::WIDGET ? selectedWidget : renderingWidget;
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
    case SelectionMode::WIDGET:
      return selectedWidget->size( );
    case SelectionMode::AREA:
    case SelectionMode::FULL:
    default:
      return screen == nullptr ? renderingWidget->size( ) : screen->size( );
  }
}

QSize RecorderGeneralData::getFinalDestinationSize( ) const
{
  switch ( destinationMode )
  {
    case DestinationMode::FIXED:
      return destinationSize;
    case DestinationMode::SCALED:
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
    case SelectionMode::AREA:
      return sourceViewport;
    case SelectionMode::WIDGET:
    case SelectionMode::FULL:
    default:
      return { 0 , 0 , 1 , 1 };
  }
}
