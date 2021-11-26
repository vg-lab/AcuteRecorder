//
// Created by Gael Rial Costas on 16/8/21.
//

#include <acuterecorder/acuterecorder.h>

#include "MainWindowRegion.h"

#include <QApplication>
#include <QScreen>
#include <QProgressBar>
#include <QMessageBox>
#include <QFileInfo>

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

  RecorderSettings builder = RecorderSettings( );

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

  if(!builder.isValid())
  {
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("Invalid configuration"));
    msgBox.setText(tr("Some recording options are unset or invalid."));
    msgBox.setIcon(QMessageBox::Icon::Critical);
    msgBox.exec();
    return;
  }

  QFileInfo outputVideo{builder.getOutputPath()};
  if(outputVideo.exists())
  {
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("Output video exists"));
    msgBox.setText(tr("The output video '%1' already exists. Overwrite?.").arg(outputVideo.absoluteFilePath()));
    msgBox.setStandardButtons(QMessageBox::Cancel|QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Icon::Critical);
    const auto result = msgBox.exec();

    if(result != QMessageBox::Ok) return;
  }

  screenComboBox_->setEnabled(false);
  selectionModeRegion_->setEnabled(false);
  destinationModeRegion_->setEnabled(false);
  outputRegion_->setEnabled(false);

  // We create the config and the recorder.
  recorder_ = new Recorder( builder );

  // The recorder is ready to go, we just have to start the timer that
  // signals the recorder to take a frame!

  QObject::connect( &timer_ , SIGNAL( timeout( )) ,
                    recorder_ , SLOT( takeFrame( )) );
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

  QObject::connect(
    recorder_ , SIGNAL( bufferSizeChange( int )) ,
    queueSizeBar_ , SLOT( setValue( int ))
  );

  QObject::connect(
    recorder_ , SIGNAL( finished( )) ,
    startStopButton_ , SLOT( onFinish( ))
  );

  startStopButton_->onStart( );
}

void MainWindowRegion::stopRecording( )
{
  if ( recorder_ == nullptr ) return;
  timer_.stop();
  QObject::disconnect( &timer_ , SIGNAL( timeout( )) ,
                       recorder_ , SLOT( takeFrame( )) );

  recorder_->stop( );
  recorder_ = nullptr;

  screenComboBox_->setEnabled(true);
  selectionModeRegion_->setEnabled(true);
  destinationModeRegion_->setEnabled(true);
  outputRegion_->setEnabled(true);
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
