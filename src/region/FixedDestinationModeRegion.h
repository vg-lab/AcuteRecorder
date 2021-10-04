//
// Created by Gael Rial Costas on 17/8/21.
//

#ifndef QTRECORDER_FIXEDDESTINATIONMODEREGION_H
#define QTRECORDER_FIXEDDESTINATIONMODEREGION_H


#include <QWidget>
#include <QLineEdit>
#include "../data/RecorderGeneralData.h"

class FixedDestinationModeRegion : public QWidget
{

  RecorderGeneralData *data_;
  QLineEdit *width_;
  QLineEdit *height_;

  void onWidthChange( );

  void onHeightChange( );

public:

  FixedDestinationModeRegion( QWidget *parent , RecorderGeneralData *data );

  RecorderGeneralData *data( ) const;

  QLineEdit *widthEdit( ) const;

  QLineEdit *heightEdit( ) const;

};


#endif //QTRECORDER_FIXEDDESTINATIONMODEREGION_H
