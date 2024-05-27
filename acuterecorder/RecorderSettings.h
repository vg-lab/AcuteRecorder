/*
 * Copyright (c) 2021-2024 VG-Lab/URJC.
 *
 * Authors: Gael Rial Costas <gael.rial.costas@urjc.es>
 *
 * This file is part of AcuteRecorder <https://github.com/vg-lab/AcuteRecorder>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef ACUTERECORDER_RECORDERSETTINGS_H
#define ACUTERECORDER_RECORDERSETTINGS_H

#include <acuterecorder/api.h>
#include <map>

#include <utility>
#include <QRectF>
#include <QString>
#include <QVariant>
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
  std::pair< QString , bool > storageWorker_{ "" , false };

  bool stabilizeFramerate_ = false;
  std::map< QString , QVariant > extraSettings_;

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
   * Makes the given input the input of the settings.
   * @param input the input.
   * @return this builder.
   */
  RecorderSettings& input( const Input& input );

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
  RecorderSettings& outputSize( const QSize& size );

  /**
   * Sets as the size of the output video the
   * input size scaled by the given scale.
   *
   * You must setup the input and the input area before using this method!
   *
   * @param scale the scale.
   * @return this builder.
   */
  RecorderSettings& outputScaledSize( QSizeF scale );

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
   * Sets the name of the storage worker of the recorder to build.
   *
   * You can retrieve all storage workers using Recorder::getWorkerBuilders().
   *
   * @param worker the worker. Example: ffmpeg
   * @return this builder.
   */
  RecorderSettings& storageWorker( const QString& worker );

  /**
   * Returns the name of storage worker of the recorder to build.
   *
   * You can retrieve all storage workers using Recorder::getWorkerBuilders().
   *
   * @return the name of the storage worker.
   */
  QString getStorageWorker( ) const;

  /**
   * Makes the recorder to stabilize its framerate, duplicating
   * or skipping frames if needed.
   * This value is optional and false by default.
   * @return this builder.
   */
  RecorderSettings& stabilizeFramerate( bool stabilize );

  /**
   * Returns whether the recorder has to stabilize the framerate,
   * duplicating or skipping frames if needed.
   * @return whether framerate should be stabilized.
   */
  bool shouldStabilizeFramerate( );

  /**
 * Returns the extra settings value inside these settings that matches
 * the given key.
 * @param key the key.
 * @return the value.
 */
  QVariant getExtraSetting( const QString& key ) const;

  /**
   * Sets a extra settings value inside these settings.
   * @param key the key of the setting.
   * @param value the value of the setting.
   * @return this builder.
   */
  RecorderSettings&
  setExtraSetting( const QString& key , const QVariant& value );

  /**
   * Returns whether this recorder has all its values set.
   * @return whether this recorder has all its values set.
   */
  bool isValid( ) const;

  /**
   * Sends a debug message containing information about all
   * invalid parameters in these settings.
   */
  void invalidParametersDebug( ) const;

};


#endif //ACUTERECORDER_RECORDERSETTINGS_H
