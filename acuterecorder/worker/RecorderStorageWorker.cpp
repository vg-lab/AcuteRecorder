//
// Created by gaeqs on 12/14/21.
//

#include "RecorderStorageWorker.h"

void RecorderStorageWorker::run( )
{ }

RecorderStorageWorker::RecorderStorageWorker( QObject *parent )
  : QThread( parent )
{ }

void RecorderStorageWorker::push( std::shared_ptr< QImage > image )
{
  printf( "Unused image %p" , image.get( ));
}

void RecorderStorageWorker::stop( )
{ }