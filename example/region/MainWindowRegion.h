//
// Created by Gael Rial Costas on 16/8/21.
//

#ifndef QTRECORDER_MAINWINDOWREGION_H
#define QTRECORDER_MAINWINDOWREGION_H

#include <QWidget>
#include <QVBoxLayout>

class SelectionArea;
class ScreenComboBox;
class SelectionModeRegion;
class DestinationModeRegion;
class OutputRegion;
class StartStopButton;
class Recorder;
class QProgressBar;

class MainWindowRegion : public QWidget
{
Q_OBJECT

  SelectionArea *selectionArea_;
  ScreenComboBox *screenComboBox_;
  SelectionModeRegion *selectionModeRegion_;
  DestinationModeRegion *destinationModeRegion_;
  OutputRegion *outputRegion_;
  StartStopButton *startStopButton_;
  QProgressBar* queueSizeBar_;

  Recorder *recorder_;

signals:

  void terminated( );

protected:

  void closeEvent( QCloseEvent *event ) override;

public:

  MainWindowRegion( QWidget *parent , QWidget *root );

public slots:

  void startRecording( );

  void stopRecording( );

  void toggleRecording( );

private slots:

  void deleteRecorder( );

};


#endif //QTRECORDER_MAINWINDOWREGION_H
