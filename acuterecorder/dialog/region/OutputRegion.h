//
// Created by Gael Rial Costas on 17/8/21.
//

#ifndef QTRECORDER_OUTPUTREGION_H
#define QTRECORDER_OUTPUTREGION_H

#include <QWidget>
#include <QString>

class QLineEdit;

class QComboBox;

class WorkerBuilder;

struct RSWParameters;

class OutputRegion : public QWidget
{
Q_OBJECT

  QLineEdit *outputTextField_;
  QComboBox *workers_;
  bool folderMode_;

public:

  explicit OutputRegion( QWidget *parent , const RSWParameters& parameters );

  QString getOutputPath( ) const;

  QString getWorkerName( ) const;

  bool isFolderMode( ) const;

private slots:

  void openFileOrFolderDialog( );

  void openFileDialog( );

  void openFolderDialog( );

  void changeFolderMode( const QString& worker );

};


#endif //QTRECORDER_OUTPUTREGION_H
