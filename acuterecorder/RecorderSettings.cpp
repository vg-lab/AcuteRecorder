//
// Created by gaelr on 18/11/2021.
//

#include "RecorderSettings.h"

#include <QRectF>
#include <stdexcept>

RecorderSettings::RecorderSettings( )
{

}

RecorderSettings& RecorderSettings::input( QWidget *widget )
{
  input_ = { Input( widget ) , true };
  return *this;
}

RecorderSettings& RecorderSettings::input( QScreen *screen )
{
  input_ = { Input( screen ) , true };
  return *this;
}

RecorderSettings&
RecorderSettings::inputArea( const QRectF& area )
{
  inputArea_ = { area , true };
  return *this;
}

RecorderSettings&
RecorderSettings::outputPath( const QString& path )
{
  outputPath_ = { path , true };
  return *this;
}

RecorderSettings
RecorderSettings::outputSize( const QSize& size )
{
  outputSize_ = { size , true };
  return *this;
}

RecorderSettings
RecorderSettings::outputScaledSize( const QSizeF scale )
{
  if ( !inputArea_.second )
  {
    throw std::invalid_argument(
      "This method requires an input area to be set."
    );
  }

  if ( !input_.second )
  {
    throw std::invalid_argument(
      "This method requires an input to be set."
    );
  }

  QSize iSize = input_.first.getSize( );
  QSizeF size = inputArea_.first.size( );
  outputSize_ = { QSize(
    static_cast<int> (iSize.width( ) * size.width( ) * scale.width( )) ,
    static_cast<int> (iSize.height( ) * size.height( ) * scale.height( ))
  ) , true };
  return *this;
}


RecorderSettings& RecorderSettings::fps( int fps )
{
  fps_ = { fps , true };
  return *this;
}

Input RecorderSettings::getInput( ) const
{
  if ( !input_.second )
  {
    throw std::invalid_argument( "Input has not been set!" );
  }

  return input_.first;
}

QRectF RecorderSettings::getInputArea( ) const
{
  if ( !inputArea_.second )
  {
    throw std::invalid_argument( "Input area has not been set!" );
  }
  return inputArea_.first;
}

QString RecorderSettings::getOutputPath( ) const
{
  if ( !outputPath_.second )
  {
    throw std::invalid_argument( "Output path has not been set!" );
  }
  return outputPath_.first;
}

QSize RecorderSettings::getOutputSize( ) const
{
  if ( !outputSize_.second )
  {
    throw std::invalid_argument( "Output size has not been set!" );
  }
  return outputSize_.first;
}

int RecorderSettings::getFPS( ) const
{
  if ( !fps_.second )
  {
    throw std::invalid_argument( "FPS has not been set!" );
  }
  return fps_.first;
}

bool RecorderSettings::isValid( ) const
{
  return input_.second && inputArea_.second && outputPath_.second
         && outputSize_.second && fps_.second;
}
