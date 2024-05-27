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

#include "DestinationModeRegion.h"

#include <QHBoxLayout>
#include <QRadioButton>
#include <QLabel>
#include <QVariant>

#include <dialog/element/SelectionArea.h>
#include <dialog/region/FixedDestinationModeRegion.h>
#include <dialog/region/ScaledDestinationModeRegion.h>
#include <dialog/RSWParameters.h>

#include <dialog/constant/Styles.h>

DestinationModeRegion::DestinationModeRegion( QWidget *parent ,
                                              SelectionArea *selectionArea ,
                                              const RSWParameters& parameters )
  : QWidget( parent )
  , selectionArea_( selectionArea )
  , fixed_( new QRadioButton( "Fixed" , this ))
  , scaled_( new QRadioButton( "Scaled" , this ))
  , fixedRegion_( new FixedDestinationModeRegion(
    this , parameters.defaultFixedOutputSize ))
  , scaleRegion_( new ScaledDestinationModeRegion(
    this , parameters.defaultScaledOutputSize ))
  , finalSizeLabel_( new QLabel( this ))
{

  auto layout = new QHBoxLayout( this );
  layout->setAlignment( Qt::AlignLeft );
  layout->setMargin( 0 );

  setProperty( "class" , styles::REGION_DESTINATION_MODE );
  setLayout( layout );

  auto label = new QLabel( "Output size:" );
  label->setProperty( "class" , styles::INFO_LABEL );

  fixed_->setProperty( "class" , styles::SELECTION_RADIO_BUTTON );
  scaled_->setProperty( "class" , styles::DESTINATION_RADIO_BUTTON );

  refreshOutputSize( );

  layout->addWidget( label );
  layout->addWidget( fixed_ );
  layout->addWidget( scaled_ );
  layout->addWidget( scaleRegion_ );
  layout->addWidget( fixedRegion_ );
  layout->addWidget( finalSizeLabel_ );
  layout->addStretch( );

  fixedRegion_->hide( );

  if ( parameters.defaultOutputSizeScaled )
  {
    scaled_->setChecked( true );
  }
  else
  {
    fixed_->setChecked( true );
  }

  label->setToolTip(
    "Here you can configure the size of the output video.\n"
    "You can configure the output in two different ways:\n"
    "Fixed: defines the output size explicitly.\n"
    "Scaled: defines the output size depending on the input's size.\n"
    "The text at the end of this row shows you the final output size."
  );

  QObject::connect(
    fixed_ , SIGNAL( toggled( bool )) ,
    this , SLOT( refreshRegion( ))
  );

  QObject::connect(
    selectionArea_ , SIGNAL( inputSizeChange( QSize )) ,
    this , SLOT( refreshOutputSize( ))
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

  refreshOutputSize( );
}

void DestinationModeRegion::refreshOutputSize( )
{
  QSize size;
  if ( fixed_->isChecked( ))
  {
    size = fixedRegion_->getDestinationSize( );
  }
  else
  {
    QSize input = selectionArea_->getSelectedInput( ).getSize( );
    QRectF viewport = selectionArea_->getViewport( );
    QSizeF scaled = scaleRegion_->getDestinationScale( );
    size = QSize(
      static_cast<int>(scaled.width( ) * input.width( ) * viewport.width( )) ,
      static_cast<int>(scaled.height( ) * input.height( ) * viewport.height( ))
    );
  }
  finalSizeLabel_->setText(
    QString::number( size.width( )) + "x" + QString::number( size.height( ))
  );
}