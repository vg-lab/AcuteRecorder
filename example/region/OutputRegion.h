//
// Created by Gael Rial Costas on 17/8/21.
//

#ifndef QTRECORDER_OUTPUTREGION_H
#define QTRECORDER_OUTPUTREGION_H

#include <QWidget>
#include <QString>

class QLineEdit;

class OutputRegion : public QWidget
{
  QLineEdit *outputTextField_;

public:

  explicit OutputRegion( QWidget *parent );

  QString getOutputPath( );


private slots:

  void openFileDialog( );

};


#endif //QTRECORDER_OUTPUTREGION_H
