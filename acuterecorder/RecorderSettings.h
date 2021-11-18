//
// Created by gaelr on 18/11/2021.
//

#ifndef ACUTERECORDER_RECORDERSETTINGS_H
#define ACUTERECORDER_RECORDERSETTINGS_H

#include <QRectF>
#include <QString>
#include <QSize>

#include "Input.h"

class RecorderSettings
{

  Input input_;
  QRectF inputArea_;
  QString outputPath_;
  QSize outputSize_;
  int fps_;

public:

  RecorderSettings( const Input& input , const QRectF& inputArea ,
                    const QString& outputPath , const QSize& outputSize ,
                    int fps );

  const Input& getInput( ) const;

  void setInput( const Input& input );

  const QRectF& getInputArea( ) const;

  void setInputArea( const QRectF& inputArea );

  const QString& getOutputPath( ) const;

  void setOutputPath( const QString& outputPath );

  const QSize& getOutputSize( ) const;

  void setOutputSize( const QSize& outputSize );

  int getFps( ) const;

  void setFps( int fps );

};


#endif //ACUTERECORDER_RECORDERSETTINGS_H
