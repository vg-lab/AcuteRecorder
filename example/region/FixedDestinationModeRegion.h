//
// Created by Gael Rial Costas on 17/8/21.
//

#ifndef QTRECORDER_FIXEDDESTINATIONMODEREGION_H
#define QTRECORDER_FIXEDDESTINATIONMODEREGION_H


#include <QWidget>
#include <QLineEdit>


class QSpinBox;

class FixedDestinationModeRegion : public QWidget
{

Q_OBJECT

  QSpinBox *width_;
  QSpinBox *height_;

public:

  explicit FixedDestinationModeRegion( QWidget *parent );

  QSize getDestinationSize( ) const;

};


#endif //QTRECORDER_FIXEDDESTINATIONMODEREGION_H
