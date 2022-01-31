//
// Created by gaelr on 18/01/2022.
//

#include "RecorderSettingsDialog.h"

#include <acuterecorder/RecorderSettings.h>
#include <acuterecorder/Recorder.h>
#include <acuterecorder/dialog/RecordingSettingsWidget.h>
#include <acuterecorder/dialog/util/APIUtils.h>
#include <acuterecorder/dialog/RSWParameters.h>

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
