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

#include "FixedDestinationModeRegion.h"

#include <QHBoxLayout>
#include <QSpinBox>

#include <dialog/constant/Styles.h>

FixedDestinationModeRegion::FixedDestinationModeRegion( QWidget *parent ,
                                                        QSize defaultSize )
  : QWidget( parent ) ,
    width_( new QSpinBox( this )) ,
    height_( new QSpinBox( this ))
{

  auto layout = new QHBoxLayout( this );
  layout->setAlignment( Qt::AlignLeft );
  layout->setMargin( 0 );

  setProperty( "class" , styles::REGION_FIXED_DESTINATION_MODE );
  setLayout( layout );

  width_->setMinimum( 1 );
  height_->setMinimum( 1 );

  width_->setMaximum( 10000 );
  height_->setMaximum( 10000 );

  width_->setValue( defaultSize.width( ));
  height_->setValue( defaultSize.height( ));

  width_->setProperty( "class" , styles::FIXED_WIDTH );
  height_->setProperty( "class" , styles::FIXED_HEIGHT );

  layout->addWidget( width_ );
  layout->addWidget( height_ );
}

QSize FixedDestinationModeRegion::getDestinationSize( ) const
{
  return { width_->value( ) , height_->value( ) };
}
