//
// Created by Gael Rial Costas on 16/8/21.
//

#include <acuterecorder/acuterecorder.h>

#include <iostream>
#include "StartStopButton.h"

#include <constant/Styles.h>

StartStopButton::StartStopButton( QWidget *parent , RecorderGeneralData *d )
  : QPushButton( parent ) , data_( d ) , recorder_( ) , recording_( false ) ,
    timer_( nullptr )
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

  if ( recording_ )
  {
    recorder_->stop( );
  }
  else
  {
    auto builder = RecorderSettingsBuilder( );
    if ( data_->screen == nullptr )
    {
      builder.input( data_->getFinalWidgetToRender( ));
    }
    else
    {
      builder.input( data_->screen );
    }

    builder
      .inputArea( data_->sourceViewport )
      .outputPath( data_->output )
      .fps( data_->fps );

    if ( data_->destinationMode == DestinationMode::SCALED )
    {
      builder.outputScaledSize( data_->destinationScale );
    }
    else
    {
      builder.outputSize( data_->destinationSize );
    }

    auto settings = builder.build( );
    recorder_ = new Recorder( settings );
    recording_ = true;

    connect(
      recorder_ , &Recorder::finished ,
      this , &StartStopButton::onFinish
    );

    timer_ = new QTimer( this );
    connect(
      timer_ , &QTimer::timeout ,
      recorder_ , &Recorder::takeFrame ,
      Qt::DirectConnection
    );
    connect(
      recorder_ , SIGNAL( finished( )) ,
      timer_ , SLOT( deleteLater( ))
    );

    timer_->start( 1000 / settings.getFps( ));

    setText( "Stop" );
    setProperty( "running" , true );
    // Refreshes the style
    setStyleSheet( "/**/" );
  }
}

void StartStopButton::onFinish( )
{

  disconnect(
    recorder_ , &Recorder::finished ,
    this , &StartStopButton::onFinish
  );

  recorder_->deleteLater();


  recording_ = false;
  setText( "Start" );
  setProperty( "running" , false );
  // Refreshes the style
  setStyleSheet( "/**/" );
}
