//
// Created by Gael Rial Costas on 17/8/21.
//

#include "ScaledDestinationModeRegion.h"

#include <QHBoxLayout>
#include <QDoubleSpinBox>

#include <dialog/constant/Styles.h>

ScaledDestinationModeRegion::ScaledDestinationModeRegion( QWidget *parent ,
                                                          QSizeF defaultScale )
  : QWidget( parent ) ,
    width_( new QDoubleSpinBox( this )) ,
    height_( new QDoubleSpinBox( this ))
{

  auto layout = new QHBoxLayout( this );
  layout->setAlignment( Qt::AlignLeft );
  layout->setMargin( 0 );

  setProperty( "class" , styles::REGION_SCALED_DESTINATION_MODE );
  setLayout( layout );

  width_->setMinimum( 0.01 );
  height_->setMinimum( 0.01 );

  width_->setValue( defaultScale.width( ));
  height_->setValue( defaultScale.height( ));

  width_->setProperty( "class" , styles::SCALED_WIDTH );
  height_->setProperty( "class" , styles::SCALED_HEIGHT );

  layout->addWidget( width_ );
  layout->addWidget( height_ );
}

QSizeF ScaledDestinationModeRegion::getDestinationScale( ) const
{
  return { width_->value( ) , height_->value( ) };
}
