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

#ifndef QTRECORDER_SCALEDDESTINATIONMODEREGION_H
#define QTRECORDER_SCALEDDESTINATIONMODEREGION_H

#include <QWidget>

class QDoubleSpinBox;

class ScaledDestinationModeRegion : public QWidget
{

Q_OBJECT

  QDoubleSpinBox *width_;
  QDoubleSpinBox *height_;

public:

  explicit ScaledDestinationModeRegion( QWidget *widget, QSizeF defaultScale);

  QSizeF getDestinationScale( ) const;

};


#endif //QTRECORDER_SCALEDDESTINATIONMODEREGION_H
