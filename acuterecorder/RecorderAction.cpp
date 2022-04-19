/*
 * Copyright (c) 2022 VG-LAB/URJC
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

// Project
#include <RecorderAction.h>

// Qt
#include <QIcon>

RecorderAction::RecorderAction(QObject *parent)
: QAction{parent}
{
  setText(tr("Recorder"));
  setShortcut(QKeySequence("Ctrl+R"));
  setCheckable(true);
  setIconVisibleInMenu(true);

  m_timer.setInterval(1000);
  m_timer.setSingleShot(false);

  changeUI(false);

  connect(this, SIGNAL(toggled(bool)),
          this, SLOT(changeUI(bool)));

  connect(&m_timer, SIGNAL(timeout()),
          this,     SLOT(swapIcon()));
}

void RecorderAction::changeUI(bool state)
{
  const QString checkedStr = "Recorder (currently recording, click to stop)";
  const QString uncheckedStr = "Recorder";

  setIcon(QIcon(":/Recorder/icons/record.svg"));
  if(state)
  {
    setText(checkedStr);
    setToolTip(checkedStr);
    setStatusTip(checkedStr);
    if(!m_timer.isActive()) m_timer.start();
  }
  else
  {
    setText(uncheckedStr);
    setToolTip(uncheckedStr);
    setStatusTip(uncheckedStr);
    if(m_timer.isActive()) m_timer.stop();
  }
}

void RecorderAction::swapIcon()
{
  static unsigned char counter = 0;

  if(isChecked())
  {
    const auto iconStr = QString(":/Recorder/icons/stop_%1.svg").arg(++counter % 2);
    setIcon(QIcon(iconStr));
  }
}
