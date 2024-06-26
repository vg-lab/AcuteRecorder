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
  , defaultOutput_ (parameters.defaultOutput)
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
      if(workers_->count() == 0) changeFolderMode(item.first);
      workers_->addItem( item.first );

      if ( item.first == parameters.defaultWorker )
      {
        workers_->setCurrentIndex( workers_->count( ) - 1 );
        changeFolderMode(item.first);
      }
    }
  }

  label->setVisible( parameters.showOutput );
  outputTextField_->setVisible( parameters.showOutput );

  workers_->setEnabled(workers_->count() > 1 && parameters.showWorker);

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

  changeFolderMode( workers_->currentText( ));
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
    "*.mkv" ,
    nullptr ,
    QFileDialog::DontUseNativeDialog
  );
  if ( !result.isEmpty( ))
  {
    if(!result.endsWith(".mkv",Qt::CaseInsensitive)) result += ".mkv";

    outputTextField_->setText( result );
  }
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
  auto worker = Recorder::getWorkerBuilder( workerName );
  if ( worker )
  {
    folderMode_ = worker->isOutputAFolder( );

    if(folderMode_)
      outputTextField_->setText( QDir::homePath() );
    else
      outputTextField_->setText( QDir::home().absoluteFilePath(defaultOutput_ ));
  }
}
