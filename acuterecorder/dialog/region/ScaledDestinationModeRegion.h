//
// Created by Gael Rial Costas on 17/8/21.
//

#ifndef QTRECORDER_SCALEDDESTINATIONMODEREGION_H
#define QTRECORDER_SCALEDDESTINATIONMODEREGION_H

#include <QWidget>

class QDoubleSpinBox;

class ScaledDestinationModeRegion : public QWidget
{

Q_OBJECT

  QDoubleSpinBox *width_;
  QDoubleSpinBox *height_;

public:

  explicit ScaledDestinationModeRegion( QWidget *widget, QSizeF defaultScale);

  QSizeF getDestinationScale( ) const;

};


#endif //QTRECORDER_SCALEDDESTINATIONMODEREGION_H
