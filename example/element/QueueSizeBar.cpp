//
// Created by Gael Rial Costas on 16/8/21.
//

#include <acuterecorder/acuterecorder.h>

#include "QueueSizeBar.h"

#include <QVariant>
#include <QTimer>

#include <constant/Styles.h>

QueueSizeBar::QueueSizeBar( QWidget *parent , RecorderGeneralData *d )
  : QProgressBar( parent ) , timer_( new QTimer( this ))
{

  setProperty( "class" , styles::QUEUE_SIZE_BAR );
  QObject::connect( timer_ , &QTimer::timeout , [ this , d ]( )
  {
    setValue( d->thread != nullptr
              ? d->thread->storeManager( )->filesInQueue( )
              : 0 );
  } );

  timer_->start( 100 );
}
