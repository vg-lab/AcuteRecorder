//
// Created by gaeqs on 8/3/21.
//

#ifndef QTRECORDER_RENDERMANAGER_H
#define QTRECORDER_RENDERMANAGER_H


#include <QSize>
#include <QWidget>
#include "StoreManager.h"

class RenderManager
{

  StoreManager storeManager_;

  QWidget *widget_;
  int fps_;
  QSize size_;
  std::chrono::microseconds delayPerFrame_;

  volatile bool running_ , finished_;

  void run( );

  void render( );

public:

  RenderManager( int fps , QSize size , QWidget *widget );

  bool start( );

  void stop( );

  int FPS( ) const;

  bool setFPS( int fps );

  QSize size( );

  bool setSize( QSize size );

  StoreManager *storeManager( );

};


#endif //QTRECORDER_RENDERMANAGER_H
