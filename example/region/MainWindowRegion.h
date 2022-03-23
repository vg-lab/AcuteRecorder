//
// Created by Gael Rial Costas on 16/8/21.
//

#ifndef QTRECORDER_MAINWINDOWREGION_H
#define QTRECORDER_MAINWINDOWREGION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>

class RecorderSettingsWidget;

class StartStopButton;

class QProgressBar;

class Recorder;

class MainWindowRegion : public QWidget
{
Q_OBJECT

  RecorderSettingsWidget *settingsWidget_;
  StartStopButton *startStopButton_;
  QProgressBar *queueSizeBar_;

  // this should be unique_ptr, unable to do it because CMake common.
  Recorder *recorder_;
  QTimer timer_;

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

  /** \brief Displays the recorder error message.
   * \param[in] message Error message.
   *
   */
  void onRecorderError(const QString &message);

};


#endif //QTRECORDER_MAINWINDOWREGION_H
