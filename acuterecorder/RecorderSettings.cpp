//
// Created by Gael Rial Costas on 18/11/2021.
//

#include "RecorderSettings.h"

#include <QRectF>
#include <QDebug>

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

RecorderSettings& RecorderSettings::input( const Input& input )
{
  input_ = { input , input.getType() != InputType::INVALID };
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

RecorderSettings&
RecorderSettings::outputSize( const QSize& size )
{
  outputSize_ = { size , true };
  return *this;
}

RecorderSettings&
RecorderSettings::outputScaledSize( const QSizeF scale )
{

  if ( !inputArea_.second )
  {
    qDebug( )
      << "RecorderSettings:outputScaledSize requires the input area to be set!";
    return *this;
  }

  if ( !input_.second )
  {
    qDebug( )
      << "RecorderSettings:outputScaledSize requires the input to be set!";
    return *this;
  }

  QSize iSize = input_.first.getSize( );
  QSizeF size = inputArea_.first.size( );
  outputSize_ = { QSize(
    static_cast<int> (iSize.width( ) * size.width( ) * scale.width( )) ,
    static_cast<int> (iSize.height( ) * size.height( ) * scale.height( ))
  ) , true };
  return *this;
}


RecorderSettings& RecorderSettings::storageWorker( const QString& worker )
{
  storageWorker_ = { worker , true };
  return *this;
}


RecorderSettings& RecorderSettings::fps( int fps )
{
  fps_ = { fps , true };
  return *this;
}

RecorderSettings& RecorderSettings::stabilizeFramerate( bool stabilize )
{
  stabilizeFramerate_ = stabilize;
  return *this;
}

Input RecorderSettings::getInput( ) const
{
  return input_.first;
}

QRectF RecorderSettings::getInputArea( ) const
{
  return inputArea_.first;
}

QString RecorderSettings::getOutputPath( ) const
{
  return outputPath_.first;
}

QSize RecorderSettings::getOutputSize( ) const
{
  return outputSize_.first;
}

int RecorderSettings::getFPS( ) const
{
  return fps_.first;
}

QString RecorderSettings::getStorageWorker( ) const
{
  return storageWorker_.first;
}

bool RecorderSettings::shouldStabilizeFramerate( )
{
  return stabilizeFramerate_;
}


bool RecorderSettings::isValid( ) const
{
  return input_.second && inputArea_.second && outputPath_.second
         && outputSize_.second && fps_.second && storageWorker_.second;
}

void RecorderSettings::invalidParametersDebug( ) const
{
  if ( !input_.second )qDebug( ) << "Input is not set!";
  if ( !inputArea_.second )qDebug( ) << "Input area is not set!";
  if ( !outputPath_.second )qDebug( ) << "Output path is not set!";
  if ( !outputSize_.second )qDebug( ) << "Output size is not set!";
  if ( !fps_.second )qDebug( ) << "FPS is not set!";
  if ( !storageWorker_.second )
    qDebug( )
      << "Storage worker is not set! "
      << "Search an available worker using Recorder::getWorkerBuilders()";
}

RecorderSettings&
RecorderSettings::setExtraSetting( const QString& key , const QVariant& value )
{
  extraSettings_[ key ] = value;
  return *this;
}

QVariant RecorderSettings::getExtraSetting( const QString& key ) const
{
  const auto it = extraSettings_.find(key);
  Q_ASSERT(it != extraSettings_.end());

  return (*it).second;
}
