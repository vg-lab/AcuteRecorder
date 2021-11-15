//
// Created by Gael Rial Costas on 16/8/21.
//

#include "QueueSizeBar.h"

#include <QVariant>

#include <constant/Styles.h>
#include <render/WidgetRenderThread.h>

QueueSizeBar::QueueSizeBar( QWidget *parent , RecorderGeneralData *data )
  : QProgressBar( parent ) , timer_( new QTimer( this ))
{

  setProperty( "class" , styles::QUEUE_SIZE_BAR );
  QObject::connect( timer_ , &QTimer::timeout , [ this , data ]( )
  {
    setValue( data->thread != nullptr
              ? data->thread->storeManager( )->filesInQueue( )
              : 0 );
  } );

  timer_->start( 100 );
}