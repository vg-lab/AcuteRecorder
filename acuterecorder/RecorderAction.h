/*
 * Copyright (c) 2022-2024 VG-LAB/URJC
 *
 * Authors: Félix de las Pozas <felix.delaspozas@urjc.es>
 *
 * This file is part of AcuteRecorder
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

#ifndef ACUTERECORDER_RECORDERACTION_H_
#define ACUTERECORDER_RECORDERACTION_H_

// Project
#include <acuterecorder/api.h>

// Qt
#include <QAction>
#include <QTimer>

/** \class RecorderAction
 * \brief Implements an animated QAction for the recorder.
 *
 */
class ACUTERECORDER_API RecorderAction
:public QAction
{
    Q_OBJECT
  public:
    /** \brief RecorderAction class constructor.
     * \param[in] parent Raw pointer of the object owner of the action.
     *
     */
    explicit RecorderAction(QObject *parent = nullptr);

    /** \brief RecorderAction class virtual destructor.
     *
     */
    virtual ~RecorderAction()
    {};

  private slots:
    /** \brief Modifies the text, icon and tooltip depending on the state.
     * \param[in] state True for checked false otherwise.
     *
     */
    void changeUI(bool state);

    /** \brief Modifies the icon when the action is checked.
     *
     */
    void swapIcon();

  private:
    QTimer m_timer; /** timer to change icon when checked. */
};

#endif /* ACUTERECORDER_RECORDERACTION_H_ */
