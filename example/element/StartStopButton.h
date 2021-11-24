//
// Created by Gael Rial Costas on 16/8/21.
//

#ifndef QTRECORDER_STARTSTOPBUTTON_H
#define QTRECORDER_STARTSTOPBUTTON_H

#include <QPushButton>

class StartStopButton;

class StartStopButton : public QPushButton
{

Q_OBJECT

public:

  explicit StartStopButton( QWidget *parent );

public slots:

  void onFinish( );

  void onStart( );
};


#endif //QTRECORDER_STARTSTOPBUTTON_H
