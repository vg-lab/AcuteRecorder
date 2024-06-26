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

#include <acuterecorder/dialog/element/SelectionArea.h>
#include <acuterecorder/dialog/element/ScreenComboBox.h>
#include <acuterecorder/dialog/region/SelectionModeRegion.h>
#include <acuterecorder/dialog/region/DestinationModeRegion.h>
#include <acuterecorder/dialog/region/OutputRegion.h>
#include <acuterecorder/dialog/constant/Styles.h>
#include <acuterecorder/dialog/RSWParameters.h>
#include <acuterecorder/dialog/RecorderSettingsWidget.h>

#include <QApplication>
#include <QScreen>
#include <QFileInfo>

RecorderSettingsWidget::RecorderSettingsWidget(
  QWidget *parent ,
  const RSWParameters& parameters )
  : QWidget( parent )
  , stabilizeFramerate_( parameters.stabilizeFramerate )
{
  auto layout = new QVBoxLayout( this );

  setProperty( "class" , styles::REGION_SETTINGS_WIDGET );
  setLayout( layout );

  Q_ASSERT( !parameters.widgetsToRecord.empty( ));

  selectionArea_ = new SelectionArea(
    this , parameters.widgetsToRecord.front( ).second ,
    parameters.defaultSelectionMode );
  screenComboBox_ = new ScreenComboBox(
    this , parameters.widgetsToRecord , parameters.includeScreens );
  selectionModeRegion_ = new SelectionModeRegion( this , parameters );
  destinationModeRegion_ = new DestinationModeRegion(
    this , selectionArea_ , parameters );
  outputRegion_ = new OutputRegion( this , parameters );

  layout->addWidget( selectionArea_ , 1 );
  layout->addStretch( );
  layout->addWidget( screenComboBox_ );
  layout->addWidget( selectionModeRegion_ );
  layout->addWidget( destinationModeRegion_ );
  layout->addWidget( outputRegion_ );

  selectionModeRegion_->setVisible(
    ( parameters.showSourceParameters &&
      ( parameters.showFullSourceMode
        || parameters.showAreaSourceMode
        || parameters.showWidgetSourceMode )) ||
    parameters.showFPS );

  destinationModeRegion_->setVisible( parameters.showOutputSizeParameters );
  outputRegion_->setVisible( parameters.showOutput || parameters.showWorker );

  QObject::connect(
    screenComboBox_ , SIGNAL( inputChanged( Input )) ,
    selectionArea_ , SLOT( changeInput( Input ))
  );
  QObject::connect(
    screenComboBox_ , SIGNAL( inputChanged( Input )) ,
    selectionModeRegion_ , SLOT( changeInput( Input ))
  );
  QObject::connect(
    selectionModeRegion_ , SIGNAL( selectionModeChanged( SelectionMode )) ,
    selectionArea_ , SLOT( changeMode( SelectionMode ))
  );
}

RecorderSettings RecorderSettingsWidget::getSettings( )
{
  RecorderSettings settings = RecorderSettings( )
    .input( selectionArea_->getSelectedInput( ))
    .inputArea( selectionArea_->getViewport( ))
    .fps( selectionModeRegion_->getFPS( ))
    .outputPath( outputRegion_->getOutputPath( ))
    .storageWorker( outputRegion_->getWorkerName( ))
    .stabilizeFramerate( stabilizeFramerate_ );

  if ( destinationModeRegion_->isFixedMode( ))
  {
    settings.outputSize( destinationModeRegion_->getFixedSize( ));
  }
  else
  {
    settings.outputScaledSize( destinationModeRegion_->getScaledSize( ));
  }

  return settings;
}

bool RecorderSettingsWidget::isFolderMode( )
{
  return outputRegion_->isFolderMode( );
}
