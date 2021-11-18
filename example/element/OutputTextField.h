//
// Created by Gael Rial Costas on 16/8/21.
//

#ifndef QTRECORDER_OUTPUTTEXTFIELD_H
#define QTRECORDER_OUTPUTTEXTFIELD_H

#include <QLineEdit>

struct RecorderGeneralData;

class OutputTextField : public QLineEdit
{

  RecorderGeneralData *data_;

public:

  OutputTextField( QWidget *parent , RecorderGeneralData *data );

};


#endif //QTRECORDER_OUTPUTTEXTFIELD_H
