//
// Created by gaeqs on 8/3/21.
//

#ifndef QTRECORDER_STOREMANAGER_H
#define QTRECORDER_STOREMANAGER_H


#include <QQueue>
#include <QImage>
#include <QMutex>
#include <QWaitCondition>
#include <QFuture>

class StoreManager
{

  QQueue< QImage * > queue_;
  FILE *file_;

  volatile bool running_ , finished_;

  QMutex mutex_;
  QWaitCondition notEmptyCondition_;
  QFuture< void > future_;
  QSize size_;
  int fps_;

  volatile int filesInQueue_;

  void run( );

public:

  StoreManager( QSize size , int fps );

  bool start( );

  void stop( );

  void push( QImage *image );

  void join( );

  int FPS( ) const;

  bool setFPS( int fps );

  QSize size( );

  bool setSize( QSize size );

  int filesInQueue( );
};


#endif //QTRECORDER_STOREMANAGER_H
