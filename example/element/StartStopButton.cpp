//
// Created by Gael Rial Costas on 16/8/21.
//

#include <acuterecorder/acuterecorder.h>

#include <iostream>
#include "StartStopButton.h"

#include <constant/Styles.h>

StartStopButton::StartStopButton( QWidget *parent , RecorderGeneralData *d )
  : QPushButton( parent ) , data_( d )
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
  if ( !data_->isRecording() )
  {
    if ( acute_recorder::start_recording( data_ ))
    {
      setText( "Stop" );
      setProperty( "running" , true );
      // Refreshes the style
      setStyleSheet( "/**/" );
    }
  }
  else if ( acute_recorder::stop_recording( data_ ))
  {
    setText( "Start" );
    setProperty( "running" , false );
    // Refreshes the style
    setStyleSheet( "/**/" );
  }
}
