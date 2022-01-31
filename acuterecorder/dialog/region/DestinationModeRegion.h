//
// Created by Gael Rial Costas on 17/8/21.
//

#ifndef QTRECORDER_DESTINATIONMODEREGION_H
#define QTRECORDER_DESTINATIONMODEREGION_H

#include <QWidget>

class QRadioButton;

class FixedDestinationModeRegion;

class ScaledDestinationModeRegion;

struct RSWParameters;

class DestinationModeRegion : public QWidget
{

Q_OBJECT

  QRadioButton *fixed_;
  QRadioButton *scaled_;

  FixedDestinationModeRegion *fixedRegion_;
  ScaledDestinationModeRegion *scaleRegion_;

public:

  explicit DestinationModeRegion( QWidget *parent ,
                                  const RSWParameters& parameters );

  bool isFixedMode( ) const;

  QSize getFixedSize( ) const;

  QSizeF getScaledSize( ) const;

public slots:

  void refreshRegion( );

};


#endif //QTRECORDER_DESTINATIONMODEREGION_H
