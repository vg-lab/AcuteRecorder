//
// Created by gaelr on 18/11/2021.
//

#include "RecorderSettings.h"

#include <QRectF>

RecorderSettings::RecorderSettings( const Input& input ,
                                    const QRectF& inputArea ,
                                    const QString& outputPath ,
                                    const QSize& outputSize , int fps )
  : input_( input ) , inputArea_( inputArea ) , outputPath_( outputPath ) ,
    outputSize_( outputSize ) , fps_( fps )
{ }

const Input& RecorderSettings::getInput( ) const
{
  return input_;
}

void RecorderSettings::setInput( const Input& input )
{
  input_ = input;
}

const QRectF& RecorderSettings::getInputArea( ) const
{
  return inputArea_;
}

void RecorderSettings::setInputArea( const QRectF& inputArea )
{
  inputArea_ = inputArea;
}

const QString& RecorderSettings::getOutputPath( ) const
{
  return outputPath_;
}

void RecorderSettings::setOutputPath( const QString& outputPath )
{
  outputPath_ = outputPath;
}

const QSize& RecorderSettings::getOutputSize( ) const
{
  return outputSize_;
}

void RecorderSettings::setOutputSize( const QSize& outputSize )
{
  outputSize_ = outputSize;
}

int RecorderSettings::getFps( ) const
{
  return fps_;
}

void RecorderSettings::setFps( int fps )
{
  fps_ = fps;
}