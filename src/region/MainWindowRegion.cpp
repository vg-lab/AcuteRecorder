//
// Created by Gael Rial Costas on 16/8/21.
//

#include "MainWindowRegion.h"

#include <QComboBox>
#include <QApplication>

#include <constant/Styles.h>
#include <WidgetRenderThread.h>

MainWindowRegion::MainWindowRegion( QWidget *parent ,
                                    RecorderGeneralData *data ) :
  QWidget( parent ) , data_( data )
{
  auto layout = new QVBoxLayout( this );

  setProperty( "class" , styles::REGION_MAIN_WINDOW );
  setLayout( layout );

  selectionArea_ = new SelectionArea( this , data );
  screenComboBox_ = new ScreenComboBox( this , data , this );
  selectionModeRegion_ = new SelectionModeRegion( this , data , selectionArea_ );
  destinationModeRegion_ = new DestinationModeRegion( this , data );
  outputRegion_ = new OutputRegion( this , data );
  startStopButton_ = new StartStopButton( this , data );
  queueSizeBar_ = new QueueSizeBar( this , data );

  layout->addWidget( selectionArea_, 1);
  layout->addStretch( );
  layout->addWidget( screenComboBox_ );
  layout->addWidget( selectionModeRegion_ );
  layout->addWidget( destinationModeRegion_ );
  layout->addWidget( outputRegion_ );
  layout->addWidget( startStopButton_ );
  layout->addWidget( queueSizeBar_ );
}

RecorderGeneralData *MainWindowRegion::data( ) const
{
  return data_;
}

SelectionArea *MainWindowRegion::selectionArea( ) const
{
  return selectionArea_;
}

QueueSizeBar *MainWindowRegion::queueSizeBar( ) const
{
  return queueSizeBar_;
}

SelectionModeRegion *MainWindowRegion::selectionModeRegion( ) const
{
  return selectionModeRegion_;
}

StartStopButton *MainWindowRegion::startStopButton( ) const
{
  return startStopButton_;
}

DestinationModeRegion *MainWindowRegion::destinationModeRegion( ) const
{
  return destinationModeRegion_;
}

OutputRegion *MainWindowRegion::outputRegion( ) const
{
  return outputRegion_;
}

void MainWindowRegion::closeEvent( QCloseEvent *event )
{
  // We have to check if the thread is running before closing the window.
  if ( data_->thread != nullptr )
  {
    data_->thread->stop( );
    data_->thread->storeManager( )->join( );
    data_->thread = nullptr;
    delete data_;
  }
}
