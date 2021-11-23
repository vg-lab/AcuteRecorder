//
// Created by Gael Rial Costas on 16/8/21.
//

#include <acuterecorder/acuterecorder.h>

#include "StartStopButton.h"
#include <QVariant>

#include <constant/Styles.h>

StartStopButton::StartStopButton( QWidget *parent ) : QPushButton( parent )
{
  setProperty( "class" , styles::START_STOP_BUTTON );
  setProperty( "running" , false );
  setText( "Start" );
}

void StartStopButton::onFinish( )
{
  setText( "Start" );
  setProperty( "running" , false );
  // Refreshes the style
  setStyleSheet( "/**/" );
}

void StartStopButton::onStart( )
{
  setText( "Stop" );
  setProperty( "running" , true );
  // Refreshes the style
  setStyleSheet( "/**/" );
}
