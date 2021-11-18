//
// Created by Gael Rial Costas on 16/8/21.
//

#include "SelectionModeButton.h"

#include <constant/Styles.h>

SelectionModeButton::SelectionModeButton( QString name , QWidget *parent ,
                                          SelectionMode selectionMode ,
                                          SelectionModeRegion *region )
  : QRadioButton( name , parent ) ,
    selectionMode_( selectionMode ) , region_( region )
{

  setProperty( "class" , styles::SELECTION_RADIO_BUTTON );

  QObject::connect( this , &QAbstractButton::toggled ,
                    [ = ]( bool )
                    {
                      region->data( )->selectionMode = selectionMode_;
                      region->selectionArea( )->refreshSelectionMode( );
                    } );
}


SelectionMode SelectionModeButton::selectionMode( ) const
{
  return selectionMode_;
}

SelectionModeRegion *SelectionModeButton::region( ) const
{
  return region_;
}
