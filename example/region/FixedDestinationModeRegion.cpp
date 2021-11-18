//
// Created by Gael Rial Costas on 17/8/21.
//

#include <acuterecorder/acuterecorder.h>

#include "FixedDestinationModeRegion.h"

#include <QHBoxLayout>

#include <constant/Styles.h>

FixedDestinationModeRegion::FixedDestinationModeRegion(
  QWidget *parent ,
  RecorderGeneralData *data )
  : QWidget( parent ) , data_( data )
{

  auto layout = new QHBoxLayout( this );
  layout->setAlignment( Qt::AlignLeft );
  layout->setMargin( 0 );

  setProperty( "class" , styles::REGION_FIXED_DESTINATION_MODE );
  setLayout( layout );

  auto size = data->destinationSize;
  width_ = new QLineEdit( QString::number( size.width( )) , this );
  height_ = new QLineEdit( QString::number( size.height( )) , this );

  width_->setProperty( "class" , styles::FIXED_WIDTH );
  height_->setProperty( "class" , styles::FIXED_HEIGHT );

  layout->addWidget( width_ );
  layout->addWidget( height_ );


  QObject::connect( width_ , SIGNAL( editingFinished( )) ,
                    this , SLOT( onWidthChange( )));
  QObject::connect( height_ , SIGNAL( editingFinished( )) ,
                    this , SLOT( onHeightChange( )));
}

RecorderGeneralData *FixedDestinationModeRegion::data( ) const
{
  return data_;
}

QLineEdit *FixedDestinationModeRegion::widthEdit( ) const
{
  return width_;
}

QLineEdit *FixedDestinationModeRegion::heightEdit( ) const
{
  return height_;
}

void FixedDestinationModeRegion::onWidthChange( )
{
  bool ok;
  int value = width_->text( ).toInt( &ok );
  if ( value == data_->destinationSize.width( )) return;
  if ( !ok || value < 1 )
    width_->setText( QString::number( data_->destinationSize.width( )));
  else
    data_->destinationSize.setWidth( value );
}

void FixedDestinationModeRegion::onHeightChange( )
{
  bool ok;
  int value = height_->text( ).toInt( &ok );
  if ( value == data_->destinationSize.height( )) return;
  if ( !ok || value < 1 )
    width_->setText( QString::number( data_->destinationSize.height( )));
  else
    data_->destinationSize.setHeight( value );
}
