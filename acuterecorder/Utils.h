/*
 * Copyright (c) 2021-2022 VG-Lab/URJC.
 *
 * Authors: Felix de las Pozas Alvarez <felix.delaspozas@urjc.es>
 *
 * This file is part of AcuteRecorder <https://github.com/vg-lab/acuterecorder>
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

#ifndef ACUTERECORDER_ACUTERECORDER_UTILS_H_
#define ACUTERECORDER_ACUTERECORDER_UTILS_H_

// Project
#include <acuterecorder/Recorder.h>
#include <acuterecorder/RecorderAction.h>

// Qt
#include <QEventLoop>
#include <QMessageBox>
#include <QApplication>

namespace RecorderUtils
{
  /** \brief Returns an animated QAction for a recorder.
   *
   */
  inline QAction * recorderAction()
  {
    return new RecorderAction();
  }

  /** \brief Stops the recorder and shows a dialog while
   * waits for the recorder process to finish.
   * \param[in] recorder Recorder pointer.
   * \param[in] parent Optional raw pointer of the parent widget (needed to center the dialog).
   */
  inline void stopAndWait(Recorder *recorder, QWidget *parent = nullptr)
  {
    if(!recorder) return;

    QApplication::setOverrideCursor(Qt::WaitCursor);

    QMessageBox msgBox(parent);
    msgBox.setWindowTitle(QObject::tr("Recorder"));
    msgBox.setWindowIcon(QIcon(":/icons/ns_icon.png"));
    msgBox.setText(QObject::tr("<p align='center'>Stopping the recording...<br>Please wait.</p>"));
    msgBox.setWindowFlags(Qt::Dialog|Qt::CustomizeWindowHint|Qt::WindowTitleHint);
    msgBox.setStandardButtons(QMessageBox::NoButton);
    msgBox.setIconPixmap(QIcon(":/Recorder/icons/stop_1.svg").pixmap(QSize(32,32)));

    QEventLoop waitLoop;

    QObject::connect( recorder , SIGNAL( finished( )) ,
                     &waitLoop , SLOT( quit()));

    recorder->stop();

    msgBox.show();
    waitLoop.exec();

    QApplication::restoreOverrideCursor();
  }
}

#endif /* ACUTERECORDER_ACUTERECORDER_UTILS_H_ */
