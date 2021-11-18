//
// Created by Gael Rial Costas on 16/8/21.
//

#ifndef QTRECORDER_STARTSTOPBUTTON_H
#define QTRECORDER_STARTSTOPBUTTON_H

#include <QPushButton>

struct RecorderGeneralData;

class StartStopButton;

class StartStopButton : public QPushButton
{
  RecorderGeneralData *data_;
  Recorder *recorder_;
  bool recording_;
  QTimer *timer_;

  void run( );

public:

  StartStopButton( QWidget *parent , RecorderGeneralData *data );

public slots:

  void onFinish( );
};


#endif //QTRECORDER_STARTSTOPBUTTON_H
