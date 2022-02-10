//
// Created by gaelr on 18/01/2022.
//

#include "RecorderDialog.h"

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

  buttonBox->button(QDialogButtonBox::Ok)->setText("Start");

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
      QMessageBox::warning(this, "Invalid configuration", "The recorder settings are invalid");
      return;
    }

    recorder_ = new Recorder(settings);

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
