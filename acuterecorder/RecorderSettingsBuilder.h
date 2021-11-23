//
// Created by gaelr on 18/11/2021.
//

#ifndef ACUTERECORDER_RECORDERSETTINGSBUILDER_H
#define ACUTERECORDER_RECORDERSETTINGSBUILDER_H

#include "RecorderSettings.h"

class RecorderSettingsBuilder
{

  std::pair< Input , bool > input_{ Input( ) , false };
  std::pair< QRectF , bool > inputArea_{{ 0 , 0 , 0 , 0 } , false };
  std::pair< QString , bool > outputPath_{ QString( ) , false };
  std::pair< QSize , bool > outputSize_{{ 0 , 0 } , false };
  std::pair< int , bool > fps_{ 0 , false };

public:

  RecorderSettingsBuilder( );

  RecorderSettingsBuilder& input( QWidget *widget );

  RecorderSettingsBuilder& input( QScreen *screen );

  RecorderSettingsBuilder& inputArea( const QRectF& area );

  RecorderSettingsBuilder& outputPath( const QString& path );

  RecorderSettingsBuilder& outputSize( const QSize& size );

  RecorderSettingsBuilder& outputScaledSize( const QSizeF scale );

  RecorderSettingsBuilder& fps( int fps );

  RecorderSettings build( ) const;

};


#endif //ACUTERECORDER_RECORDERSETTINGSBUILDER_H
