//
// Created by Gael Rial Costas on 2/9/21.
//

#ifndef QTRECORDER_SCREENCOMBOBOX_H
#define QTRECORDER_SCREENCOMBOBOX_H


#include <QComboBox>

class MainWindowRegion;

class QScreen;

class ScreenComboBox : public QComboBox
{

Q_OBJECT


private slots:

  void onIndexChange( int index );

public:

  explicit ScreenComboBox( QWidget *parent );

signals:

  void screenChanged( QScreen *screen );

};


#endif //QTRECORDER_SCREENCOMBOBOX_H
