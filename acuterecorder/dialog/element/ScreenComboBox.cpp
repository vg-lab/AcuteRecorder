//
// Created by Gael Rial Costas on 2/9/21.
//

#include "ScreenComboBox.h"

#include <QApplication>
#include <QScreen>
#include <QObject>

ScreenComboBox::ScreenComboBox( QWidget *parent ,
                                const std::vector< std::pair< QString, QWidget * > >& widgets ,
                                bool includeScreens )
  : QComboBox( parent ) ,
    widgets_( widgets )
{

  for ( auto it = widgets.cbegin(); it != widgets.cend(); ++it )
  {
    addItem( (*it).first );
  }

  if ( includeScreens )
  {
    auto screens = QApplication::screens( );
    for ( const auto& item: screens )
    {
      const auto text = item->name( ) +
                  tr( " (%1x%2)" ).arg( item->size( ).width( )).arg(
                    item->size( ).height( ));
      addItem( text );
    }
  }

  QObject::connect(
    this , SIGNAL( currentIndexChanged( int )) ,
    this , SLOT( onIndexChange( int ))
  );
}

void ScreenComboBox::onIndexChange( int index )
{
  auto indexSizeT = static_cast<size_t>(index);
  // If the index is 0, then we will render the widget.
  size_t widgetsSize = widgets_.size( );
  if ( indexSizeT < widgetsSize )
  {
    Input input( widgets_[index].second );
    emit inputChanged( input );
  }
  else
  {
    Input input(
      QApplication::screens( )[static_cast<int>(indexSizeT - widgetsSize)] );
    emit inputChanged( input );
  }
}
