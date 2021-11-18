//
// Created by Gael Rial Costas on 2/9/21.
//

#ifndef QTRECORDER_SCREENCOMBOBOX_H
#define QTRECORDER_SCREENCOMBOBOX_H


#include <QComboBox>

struct RecorderGeneralData;

class MainWindowRegion;

class ScreenComboBox : public QComboBox
{

Q_OBJECT

  RecorderGeneralData *data_;
  MainWindowRegion *mainWindowRegion_;

private slots:

  void onIndexChange( int index );

public:

  ScreenComboBox( QWidget *parent , RecorderGeneralData *data ,
                  MainWindowRegion *mainWindowRegion );

  RecorderGeneralData *data( ) const;
};


#endif //QTRECORDER_SCREENCOMBOBOX_H
