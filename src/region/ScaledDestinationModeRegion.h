//
// Created by Gael Rial Costas on 17/8/21.
//

#ifndef QTRECORDER_SCALEDDESTINATIONMODEREGION_H
#define QTRECORDER_SCALEDDESTINATIONMODEREGION_H

#include <QWidget>
#include <QLineEdit>

#include <RecorderGeneralData.h>

class ScaledDestinationModeRegion : public QWidget
{

Q_OBJECT

  RecorderGeneralData *data_;
  QLineEdit *width_;
  QLineEdit *height_;

private slots:

  void onWidthChange( );

  void onHeightChange( );

public:

  ScaledDestinationModeRegion( QWidget *widget ,
                               RecorderGeneralData *data );


  RecorderGeneralData *data( ) const;

  QLineEdit *widthEdit( ) const;

  QLineEdit *heightEdit( ) const;

};


#endif //QTRECORDER_SCALEDDESTINATIONMODEREGION_H
