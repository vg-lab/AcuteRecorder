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

#ifndef QTRECORDER_SELECTIONMODEREGION_H
#define QTRECORDER_SELECTIONMODEREGION_H

#include <QWidget>
#include <acuterecorder/dialog/util/SelectionMode.h>
#include <acuterecorder/dialog/RecorderSettingsWidget.h>

class QScreen;

class QRadioButton;

class QSpinBox;

struct RSWParameters;

class SelectionModeRegion : public QWidget
{

Q_OBJECT

  QRadioButton *fullButton_;
  QRadioButton *areaButton_;
  QRadioButton *widgetButton_;
  QSpinBox *fpsSpinBox_;

public:

  explicit SelectionModeRegion( QWidget *parent ,
                                const RSWParameters& parameters );

  SelectionMode getSelectionMode( ) const;

  int getFPS( ) const;

public slots:

  void changeInput( Input input );

private slots:

  void refreshSelectionMode( );

signals:

  void selectionModeChanged( SelectionMode mode );

};


#endif //QTRECORDER_SELECTIONMODEREGION_H
