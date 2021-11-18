//
// Created by gaelr on 18/11/2021.
//

#include <QSize>
#include <QRectF>
#include "RecorderSettingsBuilder.h"

RecorderSettingsBuilder::RecorderSettingsBuilder( )
{

}

RecorderSettingsBuilder& RecorderSettingsBuilder::input( QWidget *widget )
{
  input_ = { Input( widget ) , true };
  return *this;
}

RecorderSettingsBuilder& RecorderSettingsBuilder::input( QScreen *screen )
{
  input_ = { Input( screen ) , true };
  return *this;
}

RecorderSettingsBuilder&
RecorderSettingsBuilder::inputArea( const QRectF& area )
{
  inputArea_ = { area , true };
  return *this;
}

RecorderSettingsBuilder&
RecorderSettingsBuilder::outputPath( const QString& path )
{
  outputPath_ = { path , true };
  return *this;
}

RecorderSettingsBuilder&
RecorderSettingsBuilder::outputSize( const QSize& size )
{
  outputSize_ = { size , true };
  return *this;
}

RecorderSettingsBuilder&
RecorderSettingsBuilder::outputScaledSize( const QSizeF scale )
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

  QSize iSize = input_.first.getSize();
  QSizeF size = inputArea_.first.size( );
  outputSize_ = { QSize(
    static_cast<int> (iSize.width() * size.width( ) * scale.width( )) ,
    static_cast<int> (iSize.height() * size.height( ) * scale.height( ))
  ) , true };
  return *this;
}


RecorderSettingsBuilder& RecorderSettingsBuilder::fps( int fps )
{
  fps_ = { fps , true };
  return *this;
}

RecorderSettings RecorderSettingsBuilder::build( )
{
  if ( !input_.second )
  {
    std::invalid_argument( "Input has not been set!" );
  }
  if ( !inputArea_.second )
  {
    std::invalid_argument( "Input area has not been set!" );
  }
  if ( !outputPath_.second )
  {
    std::invalid_argument( "Output path has not been set!" );
  }
  if ( !outputSize_.second )
  {
    std::invalid_argument( "Output size has not been set!" );
  }
  if ( !fps_.second )
  {
    std::invalid_argument( "FPS has not been set!" );
  }

  return RecorderSettings(
    input_.first ,
    inputArea_.first ,
    outputPath_.first ,
    outputSize_.first ,
    fps_.first
  );
}
