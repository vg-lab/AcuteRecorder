//
// Created by Gael Rial Costas on 17/8/21.
//

#ifndef QTRECORDER_DESTINATIONMODEREGION_H
#define QTRECORDER_DESTINATIONMODEREGION_H

#include <QWidget>

class QRadioButton;

class QLabel;

class SelectionArea;

class FixedDestinationModeRegion;

class ScaledDestinationModeRegion;

struct RSWParameters;

class DestinationModeRegion : public QWidget
{

Q_OBJECT

  SelectionArea *selectionArea_;

  QRadioButton *fixed_;
  QRadioButton *scaled_;

  FixedDestinationModeRegion *fixedRegion_;
  ScaledDestinationModeRegion *scaleRegion_;
  QLabel *finalSizeLabel_;

public:

  explicit DestinationModeRegion( QWidget *parent ,
                                  SelectionArea *selectionArea ,
                                  const RSWParameters& parameters );

  bool isFixedMode( ) const;

  QSize getFixedSize( ) const;

  QSizeF getScaledSize( ) const;

public slots:

  void refreshRegion( );

  void refreshOutputSize( );

};


#endif //QTRECORDER_DESTINATIONMODEREGION_H
