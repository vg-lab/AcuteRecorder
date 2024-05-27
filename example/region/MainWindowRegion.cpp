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

#include "MainWindowRegion.h"

#include <acuterecorder/acuterecorder.h>

#include <QApplication>
#include <QScreen>
#include <QProgressBar>
#include <QMessageBox>
#include <QFileInfo>

#include <element/StartStopButton.h>
#include <constant/Styles.h>

MainWindowRegion::MainWindowRegion( QWidget *parent , QWidget *root ) :
  QWidget( parent ) , recorder_( nullptr )
{
  auto layout = new QVBoxLayout( this );
  setProperty( "class" , example_styles::REGION_MAIN_WINDOW );
  setLayout( layout );

  RSWParameters parameters;
  parameters.widgetsToRecord.emplace_back("Test widget", root );
  parameters.stabilizeFramerate = true;
  settingsWidget_ = new RecorderSettingsWidget( this , parameters );
  startStopButton_ = new StartStopButton( this );
  queueSizeBar_ = new QProgressBar( this );

  queueSizeBar_->setProperty( "class" , example_styles::QUEUE_SIZE_BAR );
  queueSizeBar_->setFormat("Frame queue: %p frames");
  // @felix 31-01-22 what happens if there are more than 100 frames in the queue?
  queueSizeBar_->setValue(0); // init

  layout->addWidget( settingsWidget_ );
  layout->addWidget( startStopButton_ );
  layout->addWidget( queueSizeBar_ );

  QObject::connect( startStopButton_ , SIGNAL( clicked( bool )) ,
                    this ,             SLOT( toggleRecording( ))
  );
}

void MainWindowRegion::closeEvent( QCloseEvent * )
{
  if ( recorder_ != nullptr )
  {
    recorder_->stop( );
  }

  emit terminated( );
}

void MainWindowRegion::startRecording( )
{
  if ( recorder_ != nullptr ) return;

  // First we have to create our configuration. We can do it directly
  // or using the builder.

  RecorderSettings builder = settingsWidget_->getSettings( );
  if ( !builder.isValid( ))
  {
    QMessageBox msgBox( this );
    msgBox.setWindowTitle( tr( "Invalid configuration" ));
    msgBox.setText( tr( "Some recording options are unset or invalid." ));
    msgBox.setIcon( QMessageBox::Icon::Critical );
    msgBox.exec( );
    return;
  }

  QFileInfo outputVideo{ builder.getOutputPath( ) };
  if ( outputVideo.exists( ) && !settingsWidget_->isFolderMode( ))
  {
    QMessageBox msgBox( this );
    msgBox.setWindowTitle( tr( "Output video exists" ));
    msgBox.setText(
      tr( "The output video '%1' already exists. Overwrite?." ).arg(
        outputVideo.absoluteFilePath( )));
    msgBox.setStandardButtons( QMessageBox::Cancel | QMessageBox::Ok );
    msgBox.setDefaultButton( QMessageBox::Ok );
    msgBox.setIcon( QMessageBox::Icon::Critical );
    const auto result = msgBox.exec( );

    if ( result != QMessageBox::Ok ) return;
  }

  settingsWidget_->setEnabled( false );

  // We create the config and the recorder.
  recorder_ = new Recorder( builder );

  // The recorder is ready to go, we just have to start the timer that
  // signals the recorder to take a frame!

  QObject::connect( &timer_ , SIGNAL( timeout( )) ,
                    recorder_ , SLOT( takeFrame( )));
  timer_.start( 1000 / builder.getFPS( ));

  // Signal this region when the recorder finishes recording.
  // Warning! The recorder won't stop automatically when you
  // use Recorder::stop(). You have to wait for the  image queue
  // to be empty.
  QObject::connect(
    recorder_ , SIGNAL( finished( )) ,
    this , SLOT( deleteRecorder( ))
  );

  // Queue size
  QObject::connect( recorder_,     SIGNAL(bufferSizeChange(int)),
                    queueSizeBar_, SLOT(setValue(int)));

  QObject::connect( recorder_ , SIGNAL( finished( )) ,
                    startStopButton_ , SLOT( onFinish( ))
  );

  QObject::connect( recorder_, SIGNAL(error(const QString &)),
                    this, SLOT(onRecorderError(const QString &))
  );

  startStopButton_->onStart( );
}

void MainWindowRegion::stopRecording( )
{
  if ( recorder_ == nullptr ) return;
  timer_.stop( );
  QObject::disconnect( &timer_ , SIGNAL( timeout( )) ,
                       recorder_ , SLOT( takeFrame( )));

  QApplication::setOverrideCursor( Qt::WaitCursor );

  recorder_->stop( );

  settingsWidget_->setEnabled( true );

  QApplication::restoreOverrideCursor( );
}

void MainWindowRegion::toggleRecording( )
{
  if ( !recorder_ )
  {
    startRecording( );
  }
  else
  {
    stopRecording( );
  }
}

void MainWindowRegion::deleteRecorder( )
{
  if ( recorder_ ) recorder_->deleteLater( );
  recorder_ = nullptr;
}

void MainWindowRegion::onRecorderError(const QString &message)
{
  const auto title = tr("Recorder error");
  QMessageBox::critical(this, title, message, QMessageBox::Button::Ok);
}
