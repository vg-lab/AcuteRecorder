//
// Created by Gael Rial Costas on 17/8/21.
//

#include "OutputRegion.h"

#include <acuterecorder/worker/WorkerBuilder.h>
#include <acuterecorder/Recorder.h>

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>

#include <constant/Styles.h>
#include <QComboBox>
#include <QObject>

OutputRegion::OutputRegion( QWidget *p ) : QWidget( p ) ,
                                           folderMode_( false )
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

  outputTextField_->setText( "output.mp4" );

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
    }
  }

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
    "Select output" ,
    "~/" ,
    "*.mp4"
  );
  if ( result.isEmpty( )) return;
  outputTextField_->setText( result );
}

void OutputRegion::openFolderDialog( )
{
  auto result = QFileDialog::getExistingDirectory(
    this ,
    "Select output folder" ,
    "~/"
  );
  if ( result.isEmpty( )) return;
  outputTextField_->setText( result );
}

void OutputRegion::changeFolderMode( const QString& workerName )
{
  WorkerBuilder *worker = Recorder::getWorkerBuilder( workerName );
  if ( worker == nullptr ) return;
  folderMode_ = worker->isOutputAFolder( );
}