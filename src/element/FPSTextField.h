//
// Created by Gael Rial Costas on 1/9/21.
//

#ifndef QTRECORDER_FPSTEXTFIELD_H
#define QTRECORDER_FPSTEXTFIELD_H


#include <QLineEdit>

#include <data/RecorderGeneralData.h>

class FPSTextField : public QLineEdit
{

Q_OBJECT

  RecorderGeneralData *data_;

private slots:

  void onFPSChange( );

public :

  FPSTextField( QWidget *parent , RecorderGeneralData *data );

};


#endif //QTRECORDER_FPSTEXTFIELD_H
