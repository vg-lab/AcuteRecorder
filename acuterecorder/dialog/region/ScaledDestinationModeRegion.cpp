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
