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

#include "RecorderSettingsDialog.h"

#include <acuterecorder/RecorderSettings.h>
#include <acuterecorder/Recorder.h>
#include <acuterecorder/dialog/util/APIUtils.h>
#include <acuterecorder/dialog/RSWParameters.h>
#include <acuterecorder/dialog/RecorderSettingsWidget.h>

#include <QDialogButtonBox>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QFileInfo>

RecorderSettingsDialog::RecorderSettingsDialog( QWidget *parent ,
                                                const RSWParameters& parameters )
  : QDialog( parent )
{
  setWindowTitle( "Select your recording settings" );
  resize( 600 , 600 );

  auto layout = new QVBoxLayout( this );
  setLayout( layout );

  settingsWidget_ = new RecorderSettingsWidget( this , parameters );
  auto buttonBox = new QDialogButtonBox(
    QDialogButtonBox::Ok | QDialogButtonBox::Cancel , this );

  buttonBox->button(QDialogButtonBox::Ok)->setText("Start Recording!");

  layout->addWidget( settingsWidget_ );
  layout->addWidget( buttonBox );

  QObject::connect(buttonBox, SIGNAL( rejected( )) ,
                   this,      SLOT( reject( )));

  QObject::connect(buttonBox, SIGNAL( accepted( )) ,
                   this,      SLOT( tryToAccept( )));
}

RecorderSettings RecorderSettingsDialog::getSettings( )
{
  return settingsWidget_->getSettings( );
}

void RecorderSettingsDialog::tryToAccept( )
{
  const auto settings = settingsWidget_->getSettings( );
  const auto folderMode = settingsWidget_->isFolderMode( );
  if ( api_utils::validateSettings( this , settings , folderMode ))
  {
    accept( );
  }
  else
  {
    QMessageBox::warning(this, "Invalid configuration", "The recorder settings are invalid");
  }
}
