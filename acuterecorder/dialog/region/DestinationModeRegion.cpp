//
// Created by Gael Rial Costas on 17/8/21.
//

#include "DestinationModeRegion.h"

#include <QHBoxLayout>
#include <QRadioButton>
#include <QLabel>
#include <QVariant>

#include <dialog/region/FixedDestinationModeRegion.h>
#include <dialog/region/ScaledDestinationModeRegion.h>
#include <dialog/RSWParameters.h>

#include <dialog/constant/Styles.h>

DestinationModeRegion::DestinationModeRegion( QWidget *parent ,
                                              const RSWParameters& parameters )
  : QWidget( parent ) ,
    fixed_( new QRadioButton( "Fixed" , this )) ,
    scaled_( new QRadioButton( "Scaled" , this )) ,
    fixedRegion_( new FixedDestinationModeRegion(
      this , parameters.defaultFixedOutputSize )) ,
    scaleRegion_( new ScaledDestinationModeRegion(
      this , parameters.defaultScaledOutputSize ))
{

  auto layout = new QHBoxLayout( this );
  layout->setAlignment( Qt::AlignLeft );
  layout->setMargin( 0 );

  setProperty( "class" , styles::REGION_DESTINATION_MODE );
  setLayout( layout );

  auto label = new QLabel( "Output size:" );
  label->setProperty( "class" , styles::INFO_LABEL );

  fixed_->setProperty( "class" , styles::SELECTION_RADIO_BUTTON );
  scaled_->setProperty( "class" , styles::DESTINATION_RADIO_BUTTON );

  layout->addWidget( label );
  layout->addWidget( fixed_ );
  layout->addWidget( scaled_ );
  layout->addWidget( scaleRegion_ );
  layout->addWidget( fixedRegion_ );
  layout->addStretch( );

  fixedRegion_->hide( );

  if ( parameters.defaultOutputSizeScaled )
  {
    scaled_->setChecked( true );
  }
  else
  {
    fixed_->setChecked( true );
  }

  QObject::connect(
    fixed_ , SIGNAL( toggled( bool )) ,
    this , SLOT( refreshRegion( ))
  );
}


bool DestinationModeRegion::isFixedMode( ) const
{
  return fixed_->isChecked( );
}


QSize DestinationModeRegion::getFixedSize( ) const
{
  return fixedRegion_->getDestinationSize( );
}

QSizeF DestinationModeRegion::getScaledSize( ) const
{
  return scaleRegion_->getDestinationScale( );
}


void DestinationModeRegion::refreshRegion( )
{

  // Hide, the show. Showing before hiding resizes the window.
  if ( isFixedMode( ))
  {
    scaleRegion_->hide( );
    fixedRegion_->show( );
  }
  else
  {
    fixedRegion_->hide( );
    scaleRegion_->show( );
  }

  //fixedRegion_->setVisible( fixed );
  //scaleRegion_->setHidden( fixed );
}