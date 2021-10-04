//
// Created by Gael Rial Costas on 16/8/21.
//

#ifndef QTRECORDER_MAINWINDOWREGION_H
#define QTRECORDER_MAINWINDOWREGION_H


#include <QWidget>
#include <QVBoxLayout>
#include "../data/RecorderGeneralData.h"
#include "../element/SelectionArea.h"
#include "../element/QueueSizeBar.h"
#include "SelectionModeRegion.h"
#include "../element/StartStopButton.h"
#include "DestinationModeRegion.h"
#include "OutputRegion.h"
#include "../element/ScreenComboBox.h"

class MainWindowRegion : public QWidget
{

  RecorderGeneralData *data_;

  SelectionArea *selectionArea_;
  ScreenComboBox *screenComboBox_;
  SelectionModeRegion *selectionModeRegion_;
  DestinationModeRegion *destinationModeRegion_;
  OutputRegion *outputRegion_;
  StartStopButton *startStopButton_;
  QueueSizeBar *queueSizeBar_;

protected:

  void closeEvent( QCloseEvent *event ) override;

public:

  MainWindowRegion( QWidget *parent , RecorderGeneralData *data );

  RecorderGeneralData *data( ) const;

  SelectionArea *selectionArea( ) const;

  SelectionModeRegion *selectionModeRegion( ) const;

  DestinationModeRegion *destinationModeRegion( ) const;

  OutputRegion *outputRegion( ) const;

  QueueSizeBar *queueSizeBar( ) const;

  StartStopButton *startStopButton( ) const;

};


#endif //QTRECORDER_MAINWINDOWREGION_H
