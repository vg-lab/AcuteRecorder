//
// Created by Gael Rial Costas on 2/9/21.
//

#ifndef QTRECORDER_SCREENCOMBOBOX_H
#define QTRECORDER_SCREENCOMBOBOX_H

#include <acuterecorder/api.h>
#include <acuterecorder/Input.h>

#include <QComboBox>
#include <vector>

class QScreen;

class ACUTERECORDER_API ScreenComboBox : public QComboBox
{

Q_OBJECT

  std::vector< std::pair< QString, QWidget * > > widgets_;

private slots:

  void onIndexChange( int index );

public:

  explicit ScreenComboBox( QWidget *parent ,
                           const std::vector< std::pair< QString, QWidget * > >& widgets ,
                           bool includeScreens );

signals:

  void inputChanged( Input input );

};


#endif //QTRECORDER_SCREENCOMBOBOX_H
