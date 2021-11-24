//
// Created by gaelr on 18/11/2021.
//

#ifndef ACUTERECORDER_RECORDERSETTINGS_H
#define ACUTERECORDER_RECORDERSETTINGS_H

#include <QRectF>
#include <QString>
#include <QSize>

#include "Input.h"

/**
 * Represents the configuration of a Recorder.
 */
class RecorderSettings
{

  Input input_;
  QRectF inputArea_;
  QString outputPath_;
  QSize outputSize_;
  int fps_;

public:

  /**
   * Creates the configuration.
   * @param input the input to use.
   * @param inputArea the normalized input area to render.
   * @param outputPath the path of the video.
   * @param outputSize the output size of the video.
   * @param fps the FPS of the video.
   */
  RecorderSettings( const Input& input , const QRectF& inputArea ,
                    const QString& outputPath , const QSize& outputSize ,
                    int fps );

  /**
   * Returns the input to record.
   * @return the input.
   */
  const Input& getInput( ) const;

  /**
   * Sets the input to record.
   * @param input the input.
   */
  void setInput( const Input& input );

  /**
   * Returns the normalized area of the input to record.
   * @return the normalized area of the input.
   */
  const QRectF& getInputArea( ) const;

  /**
   * Sets the normalized area of the input to record.
   * @param inputArea the normalized area.
   */
  void setInputArea( const QRectF& inputArea );

  /**
   * Returns the path of the video.
   * @return the path of the video.
   */
  const QString& getOutputPath( ) const;

  /**
   * Sets the path of the video.
   * @param outputPath the path.
   */
  void setOutputPath( const QString& outputPath );

  /**
   * Returns the size of the output video.
   * @return the size.
   */
  const QSize& getOutputSize( ) const;

  /**
   * Sets the size of the output video.
   * @param outputSize the size.
   */
  void setOutputSize( const QSize& outputSize );

  /**
   * Returns the FPS of the output video.
   * @return the FPS.
   */
  int getFps( ) const;

  /**
   * Sets the FPS of the output video.
   * @param fps tge FPS.
   */
  void setFps( int fps );

};


#endif //ACUTERECORDER_RECORDERSETTINGS_H
