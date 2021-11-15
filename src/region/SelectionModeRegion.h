//
// Created by Gael Rial Costas on 16/8/21.
//

#ifndef QTRECORDER_SELECTIONMODEREGION_H
#define QTRECORDER_SELECTIONMODEREGION_H

#include <QWidget>

#include <RecorderGeneralData.h>
#include <element/SelectionArea.h>
#include <element/SelectionModeButton.h>
#include <element/FPSTextField.h>

class SelectionModeButton;

class SelectionModeRegion : public QWidget
{

  RecorderGeneralData *data_;
  SelectionArea *selectionArea_;

  SelectionModeButton *fullButton_;
  SelectionModeButton *areaButton_;
  SelectionModeButton *widgetButton_;
  FPSTextField *fpsTextField_;

public:

  SelectionModeRegion( QWidget *parent , RecorderGeneralData *data ,
                       SelectionArea *selectionArea );

  RecorderGeneralData *data( ) const;

  SelectionArea *selectionArea( ) const;

  void refreshWidget( );
};


#endif //QTRECORDER_SELECTIONMODEREGION_H
