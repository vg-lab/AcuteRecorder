//
// Created by Gael Rial Costas on 17/8/21.
//

#include <QHBoxLayout>
#include <iostream>
#include <QLabel>
#include "DestinationModeRegion.h"
#include "../constant/Styles.h"

DestinationModeRegion::DestinationModeRegion( QWidget *parent ,
                                              RecorderGeneralData *data )
  : QWidget( parent ) , data_( data )
{

  auto layout = new QHBoxLayout( this );
  layout->setAlignment( Qt::AlignLeft );
  layout->setMargin( 0 );

  setProperty( "class" , styles::REGION_DESTINATION_MODE );
  setLayout( layout );

  fixedButton_ = new DestinationModeButton( "Fixed" , this , this , FIXED );
  scaleButton_ = new DestinationModeButton( "Scaled" , this , this , SCALED );
  fixedRegion_ = new FixedDestinationModeRegion( this , data );
  scaleRegion_ = new ScaledDestinationModeRegion( this , data );

  auto label = new QLabel( "Output size:" );
  label->setProperty( "class" , styles::INFO_LABEL );

  layout->addWidget( label );
  layout->addWidget( scaleButton_ );
  layout->addWidget( fixedButton_ );
  layout->addWidget( scaleRegion_ );
  layout->addWidget( fixedRegion_ );
  layout->addStretch();

  fixedRegion_->hide( );

  scaleButton_->setChecked( true );
}

RecorderGeneralData *DestinationModeRegion::data( ) const
{
  return data_;
}

void DestinationModeRegion::refresh( )
{
  bool fixed = data_->destinationMode == FIXED;

  // Hide, the show. Showing before hiding resizes the window.
  if ( fixed )
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
