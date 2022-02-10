//
// Created by Gael Rial Costas on 17/8/21.
//

#include "OutputRegion.h"

#include <acuterecorder/worker/WorkerBuilder.h>
#include <acuterecorder/Recorder.h>
#include <acuterecorder/dialog/constant/Styles.h>
#include <acuterecorder/dialog/RSWParameters.h>

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>

#include <QComboBox>
#include <QObject>

OutputRegion::OutputRegion( QWidget *p , const RSWParameters& parameters )
  : QWidget( p )
  , folderMode_( false )
{
  auto layout = new QHBoxLayout( this );
  layout->setAlignment( Qt::AlignLeft );
  layout->setMargin( 0 );

  setProperty( "class" , styles::REGION_OUTPUT );
  setLayout( layout );

  outputTextField_ = new QLineEdit( this );
  auto button = new QPushButton( "Select" , this );

  outputTextField_->setProperty( "class" , styles::OUTPUT_TEXT_FIELD );
  button->setProperty( "class" , styles::OUTPUT_FILE_BUTTON );

  outputTextField_->setText( parameters.defaultOutput );

  auto label = new QLabel( "Output:" );
  label->setProperty( "class" , styles::INFO_LABEL );

  auto workerLabel = new QLabel( "Worker:" );
  workerLabel->setProperty( "class" , styles::SUB_INFO_LABEL );

  workers_ = new QComboBox( this );
  workers_->setProperty( "class" , styles::WORKERS );

  layout->addWidget( label );
  layout->addWidget( outputTextField_ );
  layout->addWidget( button );
  layout->addWidget( workerLabel );
  layout->addWidget( workers_ );

  auto map = Recorder::getWorkerBuilders( );
  for ( const auto& item: map )
  {
    if ( item.second->isAvailable( ))
    {
      workers_->addItem( item.first );
      if ( item.first == parameters.defaultWorker )
      {
        workers_->setCurrentIndex( workers_->count( ) - 1 );
      }
    }
  }

  label->setVisible( parameters.showOutput );
  outputTextField_->setVisible( parameters.showOutput );
  workerLabel->setVisible( parameters.showWorker );
  workers_->setVisible( parameters.showWorker );

  label->setToolTip(
    "The output path where the video will be stored."
  );

  workerLabel->setToolTip(
    "Represents the way the video will be stored in memory."
  );

  QObject::connect(
    button , SIGNAL( pressed( )) ,
    this , SLOT( openFileOrFolderDialog( ))
  );

  QObject::connect(
    workers_ , SIGNAL( currentTextChanged(const QString &)) ,
    this , SLOT( changeFolderMode(const QString &))
  );
}

QString OutputRegion::getOutputPath( ) const
{
  return outputTextField_->text( );
}

QString OutputRegion::getWorkerName( ) const
{
  return workers_->currentText( );
}


bool OutputRegion::isFolderMode( ) const
{
  return folderMode_;
}


void OutputRegion::openFileOrFolderDialog( )
{
  if ( folderMode_ ) openFolderDialog( );
  else openFileDialog( );
}

void OutputRegion::openFileDialog( )
{
  auto result = QFileDialog::getSaveFileName(
    this ,
    tr( "Select output" ) ,
    QDir::homePath( ) ,
    "*.mp4" ,
    nullptr ,
    QFileDialog::DontUseNativeDialog
  );
  if ( !result.isEmpty( ))
    outputTextField_->setText( result );
}

void OutputRegion::openFolderDialog( )
{
  auto result = QFileDialog::getExistingDirectory(
    this ,
    tr( "Select output folder" ) ,
    QDir::homePath( ) ,
    QFileDialog::DontUseNativeDialog
  );
  if ( !result.isEmpty( ))
    outputTextField_->setText( result );
}

void OutputRegion::changeFolderMode( const QString& workerName )
{
  WorkerBuilder *worker = Recorder::getWorkerBuilder( workerName );
  if ( worker )
    folderMode_ = worker->isOutputAFolder( );
}
