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

#include "RecorderDialog.h"

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

RecorderDialog::RecorderDialog( QWidget *parent ,
                                const RSWParameters& parameters ,
                                bool takeFramesAutomatically )
  : QDialog( parent ) ,
    recorder_( nullptr ) ,
    takeFramesAutomatically_( takeFramesAutomatically )
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

  QObject::connect(
    buttonBox , SIGNAL( rejected( )) ,
    this , SLOT( reject( ))
  );

  QObject::connect(
    buttonBox , SIGNAL( accepted( )) ,
    this , SLOT( tryToAccept( ))
  );
}

Recorder *RecorderDialog::getRecorder( )
{
  return recorder_;
}

void RecorderDialog::tryToAccept( )
{
  if(!recorder_)
  {
    auto settings = settingsWidget_->getSettings( );
    bool folderMode = settingsWidget_->isFolderMode( );
    if (!api_utils::validateSettings( this , settings , folderMode ))
    {
      QMessageBox::critical(this, "Invalid configuration", "The recorder settings are invalid");
      return;
    }

    try
    {
      recorder_ = new Recorder( settings );
    } catch (const std::runtime_error& ex) {
      QMessageBox::critical(this, "Error", ex.what());
      return;
    }

    if (takeFramesAutomatically_)
    {
      auto *timer = new QTimer();

      QObject::connect(timer,     SIGNAL(timeout( )),
                       recorder_, SLOT(takeFrame( )));

      QObject::connect(recorder_, SIGNAL(finished( )),
                       timer,     SLOT(deleteLater( )));

      timer->start(1000 / settings.getFPS());
    }
  }

  accept();
}
