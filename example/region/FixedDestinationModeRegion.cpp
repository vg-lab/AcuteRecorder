//
// Created by Gael Rial Costas on 17/8/21.
//

#include <acuterecorder/acuterecorder.h>

#include "FixedDestinationModeRegion.h"

#include <QHBoxLayout>
#include <QSpinBox>

#include <constant/Styles.h>

FixedDestinationModeRegion::FixedDestinationModeRegion( QWidget *parent )
  : QWidget( parent ) ,
    width_( new QSpinBox( this )) ,
    height_( new QSpinBox( this ))
{

  auto layout = new QHBoxLayout( this );
  layout->setAlignment( Qt::AlignLeft );
  layout->setMargin( 0 );

  setProperty( "class" , styles::REGION_FIXED_DESTINATION_MODE );
  setLayout( layout );

  width_->setMinimum( 1 );
  height_->setMinimum( 1 );

  width_->setMaximum(10000);
  height_->setMaximum(10000);

  width_->setValue(1920);
  height_->setValue(1080);

  width_->setProperty( "class" , styles::FIXED_WIDTH );
  height_->setProperty( "class" , styles::FIXED_HEIGHT );

  layout->addWidget( width_ );
  layout->addWidget( height_ );
}

QSize FixedDestinationModeRegion::getDestinationSize( ) const
{
  return { width_->value( ) , height_->value( ) };
}
