//
// Created by Gael Rial Costas on 16/8/21.
//

#ifndef QTRECORDER_SELECTIONMODEREGION_H
#define QTRECORDER_SELECTIONMODEREGION_H

#include <QWidget>
#include <util/SelectionMode.h>

class QScreen;
class QRadioButton;
class QSpinBox;

class SelectionModeRegion : public QWidget
{

Q_OBJECT

  QRadioButton *fullButton_;
  QRadioButton *areaButton_;
  QRadioButton *widgetButton_;
  QSpinBox *fpsSpinBox_;

public:

  explicit SelectionModeRegion( QWidget *parent );

  SelectionMode getSelectionMode( ) const;

  int getFPS( ) const;

public slots:

  void changeScreen( QScreen *screen );

private slots:

  void refreshSelectionMode( );

signals:

  void selectionModeChanged( SelectionMode mode );

};


#endif //QTRECORDER_SELECTIONMODEREGION_H
