//
// Created by Gael Rial Costas on 16/8/21.
//

#ifndef QTRECORDER_SELECTIONMODEBUTTON_H
#define QTRECORDER_SELECTIONMODEBUTTON_H


#include <QRadioButton>

#include <data/RecorderGeneralData.h>
#include <region/SelectionModeRegion.h>

class SelectionModeRegion;

class SelectionModeButton : public QRadioButton
{

  SelectionMode selectionMode_;
  SelectionModeRegion *region_;

public:
  SelectionModeButton( QString name , QWidget *parent ,
                       SelectionMode selectionMode ,
                       SelectionModeRegion *region );

  SelectionMode selectionMode( ) const;

  SelectionModeRegion *region( ) const;

};


#endif //QTRECORDER_SELECTIONMODEBUTTON_H
