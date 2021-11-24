//
// Created by gaelr on 18/11/2021.
//

#ifndef ACUTERECORDER_RECORDERSETTINGSBUILDER_H
#define ACUTERECORDER_RECORDERSETTINGSBUILDER_H

#include "RecorderSettings.h"

/**
 * Represents a builder that creates RecorderSettings.
 *
 * You must fill all parameter of the builder to be capable of creating settings.
 */
class RecorderSettingsBuilder
{

  std::pair< Input , bool > input_{ Input( ) , false };
  std::pair< QRectF , bool > inputArea_{{ 0 , 0 , 0 , 0 } , false };
  std::pair< QString , bool > outputPath_{ QString( ) , false };
  std::pair< QSize , bool > outputSize_{{ 0 , 0 } , false };
  std::pair< int , bool > fps_{ 0 , false };

public:

  /**
   * Creates the builder.
   */
  RecorderSettingsBuilder( );

  /**
   * Makes the given widget the input of the settings.
   * @param widget the widget.
   * @return this builder.
   */
  RecorderSettingsBuilder& input( QWidget *widget );

  /**
   * Makes the given screen the input of the settings.
   * @param screen the screen.
   * @return this builder.
   */
  RecorderSettingsBuilder& input( QScreen *screen );

  /**
   * Sets the input area of the settings.
   * @param area the input area.
   * @return this builder.
   */
  RecorderSettingsBuilder& inputArea( const QRectF& area );

  /**
   * Sets the video output path of the settings.
   * @param path the output path.
   * @return this builder.
   */
  RecorderSettingsBuilder& outputPath( const QString& path );

  /**
   * Sets the size of the output video, in pixels.
   * @param size the size of the output video.
   * @return this builder.
   */
  RecorderSettingsBuilder& outputSize( const QSize& size );

  /**
   * Sets as the size of the output video the
   * input size scaled by the given scale.
   *
   * You must setup the input and the input area before using this method!
   *
   * @param scale the scale.
   * @return this builder.
   */
  RecorderSettingsBuilder& outputScaledSize( QSizeF scale );

  /**
   * Sets the FPS of the output video.
   * @param fps the FPS.
   * @return this builder.
   */
  RecorderSettingsBuilder& fps( int fps );

  /**
   * Creates a RecorderSettings.
   * @return the RecorderSettings.
   * @throws invalid_argument when a parameter of the builder is not filled.
   */
  RecorderSettings build( ) const;

};


#endif //ACUTERECORDER_RECORDERSETTINGSBUILDER_H
