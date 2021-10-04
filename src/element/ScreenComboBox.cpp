//
// Created by Gael Rial Costas on 2/9/21.
//

#include <QApplication>
#include <QScreen>
#include <QObject>
#include "ScreenComboBox.h"
#include "../region/MainWindowRegion.h"

ScreenComboBox::ScreenComboBox( QWidget *parent , RecorderGeneralData *data ,
                                MainWindowRegion *mainWindowRegion )
  : QComboBox( parent ) , data_( data ) , mainWindowRegion_( mainWindowRegion )
{

  addItem( "Widget" );

  auto screens = QApplication::screens( );
  for ( const auto& item : screens )
  {
    addItem( item->manufacturer( ) + " - " + item->model( ));
  }

  QObject::connect( this ,
                    QOverload< int >::of( &QComboBox::currentIndexChanged ) ,
                    this , &ScreenComboBox::onIndexChange );
}

RecorderGeneralData *ScreenComboBox::data( ) const
{
  return data_;
}

void ScreenComboBox::onIndexChange( int index )
{
  // If the index is 0, then we will render the widget.
  data_->screen = index == 0 ? nullptr : QApplication::screens( )[ index - 1 ];

  // We have to reset the viewport to avoid out-of-bounds renders!
  data_->sourceViewport = ViewportI( 0 , 0 , 0 , 0 );

  // And, of course, disable the widget button in the selection mode region
  // if the source is a screen.
  mainWindowRegion_->selectionModeRegion( )->refreshWidget( );
}
