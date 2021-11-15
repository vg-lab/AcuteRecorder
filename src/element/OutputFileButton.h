//
// Created by Gael Rial Costas on 17/8/21.
//

#ifndef QTRECORDER_OUTPUTFILEBUTTON_H
#define QTRECORDER_OUTPUTFILEBUTTON_H

#include "OutputTextField.h"

#include <QPushButton>

class OutputFileButton : public QPushButton
{

  OutputTextField *outputTextField_;

public:

  OutputFileButton( QWidget *parent , OutputTextField *outputTextField );

};


#endif //QTRECORDER_OUTPUTFILEBUTTON_H
