/*
 * Copyright (c) 2021-2024 VG-Lab/URJC.
 *
 * Authors: Gael Rial Costas <gael.rial.costas@urjc.es>
 *
 * This file is part of AcuteRecorder <https://github.com/vg-lab/AcuteRecorder>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

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
