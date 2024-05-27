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
