//
// Created by Gael Rial Costas on 16/8/21.
//

#ifndef QTRECORDER_QUEUESIZEBAR_H
#define QTRECORDER_QUEUESIZEBAR_H

#include <QProgressBar>

struct RecorderGeneralData;
class QTimer;

class QueueSizeBar : public QProgressBar
{

  QTimer *timer_;

public:

  QueueSizeBar( QWidget *parent , RecorderGeneralData *data );

};


#endif //QTRECORDER_QUEUESIZEBAR_H