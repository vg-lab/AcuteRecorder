//
// Created by Gael Rial Costas on 17/8/21.
//

#include "DestinationModeButton.h"
#include "../region/DestinationModeRegion.h"
#include "../constant/Styles.h"

DestinationModeButton::DestinationModeButton( const QString& text ,
                                              QWidget *parent ,
                                              DestinationModeRegion *region ,
                                              DestinationMode destinationMode )
  : QRadioButton( text , parent ) ,
    region_( region ) ,
    destinationMode_( destinationMode )
{

  setProperty( "class" , styles::DESTINATION_RADIO_BUTTON );

  QObject::connect( this , &QAbstractButton::toggled ,
                    [ = ]( bool toggled )
                    {
                      region_->data( )->destinationMode = destinationMode_;
                      region_->refresh( );
                    } );

}

DestinationMode DestinationModeButton::destinationMode( ) const
{
  return destinationMode_;
}
