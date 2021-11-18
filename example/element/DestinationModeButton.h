//
// Created by Gael Rial Costas on 17/8/21.
//

#ifndef QTRECORDER_DESTINATIONMODEBUTTON_H
#define QTRECORDER_DESTINATIONMODEBUTTON_H

#include <QRadioButton>

#include <acuterecorder/acuterecorder.h>

class DestinationModeRegion;

class DestinationModeButton : public QRadioButton
{

  DestinationModeRegion *region_;
  DestinationMode destinationMode_;

public:

  DestinationModeButton( const QString& text ,
                         QWidget *parent ,
                         DestinationModeRegion *region ,
                         DestinationMode destinationMode );

  DestinationMode destinationMode( ) const;

};


#endif //QTRECORDER_DESTINATIONMODEBUTTON_H
