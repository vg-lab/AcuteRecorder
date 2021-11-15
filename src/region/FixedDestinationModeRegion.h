//
// Created by Gael Rial Costas on 17/8/21.
//

#ifndef QTRECORDER_FIXEDDESTINATIONMODEREGION_H
#define QTRECORDER_FIXEDDESTINATIONMODEREGION_H


#include <QWidget>
#include <QLineEdit>

#include <RecorderGeneralData.h>

class FixedDestinationModeRegion : public QWidget
{
  
Q_OBJECT

  RecorderGeneralData *data_;
  QLineEdit *width_;
  QLineEdit *height_;

private slots:

  void onWidthChange( );

  void onHeightChange( );

public:

  FixedDestinationModeRegion( QWidget *parent , RecorderGeneralData *data );

  RecorderGeneralData *data( ) const;

  QLineEdit *widthEdit( ) const;

  QLineEdit *heightEdit( ) const;

};


#endif //QTRECORDER_FIXEDDESTINATIONMODEREGION_H
