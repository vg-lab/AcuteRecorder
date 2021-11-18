//
// Created by Gael Rial Costas on 17/8/21.
//

#include <acuterecorder/acuterecorder.h>

#include "ScaledDestinationModeRegion.h"

#include <QHBoxLayout>

#include <constant/Styles.h>

ScaledDestinationModeRegion::ScaledDestinationModeRegion( QWidget *widget ,
                                                          RecorderGeneralData *data )
  : QWidget( widget ) , data_( data )
{

  auto layout = new QHBoxLayout( this );
  layout->setAlignment( Qt::AlignLeft );
  layout->setMargin( 0 );

  setProperty( "class" , styles::REGION_SCALED_DESTINATION_MODE );
  setLayout( layout );

  auto size = data->destinationScale;
  width_ = new QLineEdit( QString::number( size.width( )) , this );
  height_ = new QLineEdit( QString::number( size.height( )) , this );

  width_->setProperty( "class" , styles::SCALED_WIDTH );
  height_->setProperty( "class" , styles::SCALED_HEIGHT );

  layout->addWidget( width_ );
  layout->addWidget( height_ );

  QObject::connect( width_ , SIGNAL( editingFinished( )) ,
                    this , SLOT( onWidthChange( )));
  QObject::connect( height_ , SIGNAL( editingFinished( )) ,
                    this , SLOT( onHeightChange( )));
}

RecorderGeneralData *ScaledDestinationModeRegion::data( ) const
{
  return data_;
}

QLineEdit *ScaledDestinationModeRegion::widthEdit( ) const
{
  return width_;
}

QLineEdit *ScaledDestinationModeRegion::heightEdit( ) const
{
  return height_;
}

void ScaledDestinationModeRegion::onWidthChange( )
{
  bool ok;
  float value = width_->text( ).toFloat( &ok );
  if ( value == data_->destinationScale.width( )) return;
  if ( !ok || value < 0.1 )
    width_->setText( QString::number( data_->destinationScale.width( )));
  else
    data_->destinationScale.setWidth( value );
}

void ScaledDestinationModeRegion::onHeightChange( )
{
  bool ok;
  float value = height_->text( ).toFloat( &ok );
  if ( value == data_->destinationScale.height( )) return;
  if ( !ok || value < 0.1 )
    height_->setText( QString::number( data_->destinationScale.height( )));
  else
    data_->destinationScale.setHeight( value );
}
