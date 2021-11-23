//
// Created by Gael Rial Costas on 16/8/21.
//

#include <acuterecorder/acuterecorder.h>

#include "MainWindowRegion.h"

#include <QApplication>
#include <QScreen>
#include <QTimer>
#include <QProgressBar>

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
  queueSizeBar_ = new QProgressBar( this );

  queueSizeBar_->setProperty( "class" , styles::QUEUE_SIZE_BAR );

  layout->addWidget( selectionArea_ , 1 );
  layout->addStretch( );
  layout->addWidget( screenComboBox_ );
  layout->addWidget( selectionModeRegion_ );
  layout->addWidget( destinationModeRegion_ );
  layout->addWidget( outputRegion_ );
  layout->addWidget( startStopButton_ );
  layout->addWidget( queueSizeBar_ );


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
  if(recorder_ != nullptr) {
    recorder_->stop();
  }

  emit terminated( );
}

void MainWindowRegion::startRecording( )
{
  if ( recorder_ != nullptr ) return;

  // First we have to create our configuration. We can do it directly
  // or using the builder.

  RecorderSettingsBuilder builder = RecorderSettingsBuilder( );

  auto screen = selectionArea_->getSelectedScreen( );
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

  // We create the config and the recorder.
  RecorderSettings settings = builder.build( );
  recorder_ = new Recorder( settings );

  // The recorder is ready to go, we just have to create a timer that
  // signals the recorder to take a frame!

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

  // Signal this region when the recorder finishes recording.
  // Warning! The recorder won't stop automatically when you
  // use Recorder::stop(). You have to wait for the  image queue
  // to be empty.
  QObject::connect(
    recorder_ , &Recorder::finished ,
    this , &MainWindowRegion::deleteRecorder
  );

  // Queue size

  QObject::connect(
    recorder_ , &Recorder::bufferSizeChange ,
    queueSizeBar_ , &QProgressBar::setValue
  );

  QObject::connect(
    recorder_ , &Recorder::finished ,
    startStopButton_ , &StartStopButton::onFinish
  );

  startStopButton_->onStart( );
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

  QObject::disconnect(
    recorder_ , &Recorder::bufferSizeChange ,
    queueSizeBar_ , &QProgressBar::setValue
  );

  recorder_->deleteLater( );
  recorder_ = nullptr;
}
