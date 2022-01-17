//
// Created by gaeqs on 12/14/21.
//

#include "RecorderStorageWorker.h"

void RecorderStorageWorker::run( )
{ }

RecorderStorageWorker::RecorderStorageWorker( QObject *parent )
  : QThread( parent )
{ }

void RecorderStorageWorker::push( QImage *image )
{
  printf( "Unused image %p" , image );
}

void RecorderStorageWorker::stop( )
{ }