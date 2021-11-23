//
// Created by Gael Rial Costas on 2/9/21.
//

#include <acuterecorder/acuterecorder.h>

#include "ScreenComboBox.h"

#include <QApplication>
#include <QScreen>
#include <QObject>

#include <region/MainWindowRegion.h>

ScreenComboBox::ScreenComboBox( QWidget *parent )
  : QComboBox( parent )
{

  addItem( "Widget" );

  auto screens = QApplication::screens( );
  for ( const auto& item: screens )
  {
    auto text = item->name( ) +
                tr( " (%1x%2)" ).arg( item->size( ).width( )).arg(
                  item->size( ).height( ));
    addItem( text );
  }

  QObject::connect(
    this , SIGNAL( currentIndexChanged( int )) ,
    this , SLOT( onIndexChange( int ))
  );
}

void ScreenComboBox::onIndexChange( int index )
{
  // If the index is 0, then we will render the widget.
  auto screen = index == 0
                ? nullptr
                : QApplication::screens( )[ index - 1 ];
  emit screenChanged( screen );
}
