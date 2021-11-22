//
// Created by Gael Rial Costas on 17/8/21.
//

#ifndef QTRECORDER_DESTINATIONMODEREGION_H
#define QTRECORDER_DESTINATIONMODEREGION_H


#include <QWidget>

struct RecorderGeneralData;

class QRadioButton;

class FixedDestinationModeRegion;

class ScaledDestinationModeRegion;

class DestinationModeRegion : public QWidget
{

  QRadioButton *fixed_;
  QRadioButton *scaled_;

  FixedDestinationModeRegion *fixedRegion_;
  ScaledDestinationModeRegion *scaleRegion_;

public:

  explicit DestinationModeRegion( QWidget *parent );

  bool isFixedMode( ) const;

  QSize getFixedSize( ) const;

  QSizeF getScaledSize( ) const;

public slots:

  void refreshRegion( );

};


#endif //QTRECORDER_DESTINATIONMODEREGION_H
