/*
 * Copyright (c) 2021-2024 VG-Lab/URJC.
 *
 * Authors: Gael Rial Costas <gael.rial.costas@urjc.es>
 *
 * This file is part of AcuteRecorder <https://github.com/vg-lab/AcuteRecorder>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

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
