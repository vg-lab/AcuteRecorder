//
// Created by gaelr on 18/11/2021.
//

#ifndef ACUTERECORDER_RECORDERSETTINGS_H
#define ACUTERECORDER_RECORDERSETTINGS_H

#include <acuterecorder/api.h>

#include <utility>
#include <QRectF>
#include <QString>
#include <QSize>

#include "Input.h"

/**
 * Represents a builder that creates RecorderSettings.
 *
 * You must fill all parameter of the builder to be capable of creating settings.
 */
class ACUTERECORDER_API RecorderSettings
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
  RecorderSettings( );

  /**
   * Makes the given widget the input of the settings.
   * @param widget the widget.
   * @return this builder.
   */
  RecorderSettings& input( QWidget *widget );

  /**
   * Makes the given screen the input of the settings.
   * @param screen the screen.
   * @return this builder.
   */
  RecorderSettings& input( QScreen *screen );

  /**
   * Returns the input of this recorder.
   *
   * This is the wrapper of the given QWidget or QScreen.
   *
   * @return the input.
   */
  Input getInput( ) const;

  /**
   * Sets the input area of the settings.
   * @param area the input area.
   * @return this builder.
   */
  RecorderSettings& inputArea( const QRectF& area );

  /**
   * Returns the input area of the recorder.
   *
   * This is a normalized area (from 0 to 1).
   *
   * @return the input area.
   */
  QRectF getInputArea( ) const;

  /**
   * Sets the video output path of the settings.
   * @param path the output path.
   * @return this builder.
   */
  RecorderSettings& outputPath( const QString& path );

  /**
   * Returns the output path of the settings.
   *
   * This is the path where the output video will be stored.
   *
   * @return the output path.
   */
  QString getOutputPath( ) const;

  /**
   * Sets the size of the output video, in pixels.
   * @param size the size of the output video.
   * @return this builder.
   */
  RecorderSettings outputSize( const QSize& size );

  /**
   * Sets as the size of the output video the
   * input size scaled by the given scale.
   *
   * You must setup the input and the input area before using this method!
   *
   * @param scale the scale.
   * @return this builder.
   */
  RecorderSettings outputScaledSize( QSizeF scale );

  /**
   * Returns the size of the output video, in pixels.
   *
   * @return the size.
   */
  QSize getOutputSize( ) const;

  /**
   * Sets the FPS of the output video.
   * @param fps the FPS.
   * @return this builder.
   */
  RecorderSettings& fps( int fps );

  /**
   * Returns the FPS of the output video.
   * @return the FPS.
   */
  int getFPS( ) const;

  /**
   * Returns whether this recorder has all its values set.
   * @return whether this recorder has all its values set.
   */
  bool isValid( ) const;

  /**
   * Sends a debug message containing information about all
   * invalid parameters in these settings.
   */
  void sendInvalidParametersDebugMessage( ) const;

};


#endif //ACUTERECORDER_RECORDERSETTINGS_H
