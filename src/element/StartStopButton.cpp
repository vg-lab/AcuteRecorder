//
// Created by Gael Rial Costas on 16/8/21.
//

#include <iostream>
#include "StartStopButton.h"

#include <render/WidgetRenderThread.h>
#include <constant/Styles.h>

StartStopButton::StartStopButton( QWidget *parent , RecorderGeneralData *data )
  : QPushButton( parent ) , data_( data )
{
  setProperty( "class" , styles::START_STOP_BUTTON );
  setProperty( "running" , false );
  setText( "Start" );

  QObject::connect( this , &QPushButton::clicked , [ this ]( )
  {
    run( );
  } );
}

void StartStopButton::run( )
{
  if ( !data_->thread )
  {
    data_->thread = new WidgetRenderThread( data_ );
    data_->thread->start( );
    setText( "Stop" );
    setProperty( "running" , true );
    // Refreshes the style
    setStyleSheet( "/**/" );
  }
  else
  {
    data_->thread->stop( );
    data_->thread->storeManager( )->join( );
    delete data_->thread;
    data_->thread = nullptr;
    setText( "Start" );
    setProperty( "running" , false );
    // Refreshes the style
    setStyleSheet( "/**/" );
  }
}
