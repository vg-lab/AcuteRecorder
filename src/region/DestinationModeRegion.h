//
// Created by Gael Rial Costas on 17/8/21.
//

#ifndef QTRECORDER_DESTINATIONMODEREGION_H
#define QTRECORDER_DESTINATIONMODEREGION_H


#include <QWidget>
#include "../data/RecorderGeneralData.h"
#include "../element/DestinationModeButton.h"
#include "FixedDestinationModeRegion.h"
#include "ScaledDestinationModeRegion.h"

class DestinationModeRegion : public QWidget
{

  RecorderGeneralData *data_;

  DestinationModeButton *scaleButton_;
  DestinationModeButton *fixedButton_;

  FixedDestinationModeRegion *fixedRegion_;
  ScaledDestinationModeRegion *scaleRegion_;

public:

  DestinationModeRegion( QWidget *parent , RecorderGeneralData *data );

  RecorderGeneralData *data( ) const;

  void refresh( );

};


#endif //QTRECORDER_DESTINATIONMODEREGION_H
