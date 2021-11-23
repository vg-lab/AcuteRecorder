//
// Created by Gael Rial Costas on 16/8/21.
//

#include <acuterecorder/acuterecorder.h>

#include "MainWindowRegion.h"

#include <QApplication>
#include <QScreen>
#include <QTimer>

#include <element/SelectionArea.h>
#include <element/ScreenComboBox.h>
#include <element/StartStopButton.h>

#include <region/SelectionModeRegion.h>
#include <region/DestinationModeRegion.h>
#include <region/OutputRegion.h>

#include <constant/Styles.h>

MainWindowRegion::MainWindowRegion( QWidget *parent , QWidget *root ) :
  QWidget( parent ) , recorder_( nullptr )
{
  auto layout = new QVBoxLayout( this );

  setProperty( "class" , styles::REGION_MAIN_WINDOW );
  setLayout( layout );

  selectionArea_ = new SelectionArea( this , root );
  screenComboBox_ = new ScreenComboBox( this );
  selectionModeRegion_ = new SelectionModeRegion( this );
  destinationModeRegion_ = new DestinationModeRegion( this );
  outputRegion_ = new OutputRegion( this );
  startStopButton_ = new StartStopButton( this );

  layout->addWidget( selectionArea_ , 1 );
  layout->addStretch( );
  layout->addWidget( screenComboBox_ );
  layout->addWidget( selectionModeRegion_ );
  layout->addWidget( destinationModeRegion_ );
  layout->addWidget( outputRegion_ );
  layout->addWidget( startStopButton_ );


  QObject::connect(
    screenComboBox_ , &ScreenComboBox::screenChanged ,
    selectionArea_ , &SelectionArea::changeScreen
  );
  QObject::connect(
    screenComboBox_ , &ScreenComboBox::screenChanged ,
    selectionModeRegion_ , &SelectionModeRegion::changeScreen
  );
  QObject::connect(
    selectionModeRegion_ , &SelectionModeRegion::selectionModeChanged ,
    selectionArea_ , &SelectionArea::changeMode
  );

  QObject::connect(
    startStopButton_ , &QPushButton::clicked ,
    this , &MainWindowRegion::toggleRecording
  );
}

void MainWindowRegion::closeEvent( QCloseEvent * )
{
  emit terminated( );
}

void MainWindowRegion::startRecording( )
{
  if ( recorder_ != nullptr ) return;
  auto screen = selectionArea_->getSelectedScreen( );

  RecorderSettingsBuilder builder = RecorderSettingsBuilder( );

  if ( screen != nullptr )
  {
    builder.input( screen );
  }
  else
  {
    builder.input( selectionArea_->getSelectedWidget( ));
  }

  builder.inputArea( selectionArea_->getViewport( ));
  builder.fps( selectionModeRegion_->getFPS( ));
  builder.outputPath( outputRegion_->getOutputPath( ));

  if ( destinationModeRegion_->isFixedMode( ))
  {
    builder.outputSize( destinationModeRegion_->getFixedSize( ));
  }
  else
  {
    builder.outputScaledSize( destinationModeRegion_->getScaledSize( ));
  }

  RecorderSettings settings = builder.build( );
  recorder_ = new Recorder( settings );

  auto *timer = new QTimer( recorder_ );
  QObject::connect(
    timer , &QTimer::timeout ,
    recorder_ , &Recorder::takeFrame
  );
  QObject::connect(
    recorder_ , &Recorder::finished ,
    timer , &QObject::deleteLater
  );

  timer->start( 1000 / settings.getFps( ));
  startStopButton_->onStart( );

  QObject::connect(
    recorder_ , &Recorder::finished ,
    startStopButton_ , &StartStopButton::onFinish
  );

  QObject::connect(
    recorder_ , &Recorder::finished ,
    this , &MainWindowRegion::deleteRecorder
  );
}

void MainWindowRegion::stopRecording( )
{
  if ( recorder_ == nullptr ) return;
  recorder_->stop( );
  recorder_ = nullptr;
}

void MainWindowRegion::toggleRecording( )
{
  if ( recorder_ == nullptr )
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
  recorder_->deleteLater( );
  recorder_ = nullptr;
}
