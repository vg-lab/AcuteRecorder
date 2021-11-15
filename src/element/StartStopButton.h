//
// Created by Gael Rial Costas on 16/8/21.
//

#ifndef QTRECORDER_STARTSTOPBUTTON_H
#define QTRECORDER_STARTSTOPBUTTON_H


#include <QPushButton>

#include <RecorderGeneralData.h>

class StartStopButton : public QPushButton
{

  RecorderGeneralData *data_;

  void run( );

public:

  StartStopButton( QWidget *parent , RecorderGeneralData *data );
};


#endif //QTRECORDER_STARTSTOPBUTTON_H
