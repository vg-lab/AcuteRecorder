//
// Created by Gael Rial Costas on 17/8/21.
//

#ifndef QTRECORDER_OUTPUTREGION_H
#define QTRECORDER_OUTPUTREGION_H

#include <QWidget>

#include <element/OutputTextField.h>
#include <element/OutputFileButton.h>

struct RecorderGeneralData;

class OutputRegion : public QWidget
{
  OutputTextField *outputTextField_;
  OutputFileButton *outputFileButton_;

public:

  OutputRegion( QWidget *parent , RecorderGeneralData *data );

  OutputTextField *outputTextField( ) const;

  OutputFileButton *outputFileButton( ) const;

};


#endif //QTRECORDER_OUTPUTREGION_H
