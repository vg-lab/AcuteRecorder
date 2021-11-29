//
// Created by Gael Rial Costas on 17/8/21.
//

#include "DestinationModeRegion.h"

#include <QHBoxLayout>
#include <QRadioButton>
#include <QLabel>
#include <QVariant>

#include <region/FixedDestinationModeRegion.h>
#include <region/ScaledDestinationModeRegion.h>

#include <constant/Styles.h>

DestinationModeRegion::DestinationModeRegion( QWidget *parent )
  : QWidget( parent ) ,
    fixed_( new QRadioButton( "Fixed" , this )) ,
    scaled_( new QRadioButton( "Scaled" , this )) ,
    fixedRegion_( new FixedDestinationModeRegion( this )) ,
    scaleRegion_( new ScaledDestinationModeRegion( this ))
{

  auto layout = new QHBoxLayout( this );
  layout->setAlignment( Qt::AlignLeft );
  layout->setMargin( 0 );

  setProperty( "class" , styles::REGION_DESTINATION_MODE );
  setLayout( layout );

  auto label = new QLabel( "Output size:" );
  label->setProperty( "class" , styles::INFO_LABEL );

  layout->addWidget( label );
  layout->addWidget( fixed_ );
  layout->addWidget( scaled_ );
  layout->addWidget( scaleRegion_ );
  layout->addWidget( fixedRegion_ );
  layout->addStretch( );

  fixedRegion_->hide( );

  scaled_->setChecked( true );

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