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

#ifndef QTRECORDER_DESTINATIONMODEREGION_H
#define QTRECORDER_DESTINATIONMODEREGION_H

#include <QWidget>

class QRadioButton;

class QLabel;

class SelectionArea;

class FixedDestinationModeRegion;

class ScaledDestinationModeRegion;

struct RSWParameters;

class DestinationModeRegion : public QWidget
{

Q_OBJECT

  SelectionArea *selectionArea_;

  QRadioButton *fixed_;
  QRadioButton *scaled_;

  FixedDestinationModeRegion *fixedRegion_;
  ScaledDestinationModeRegion *scaleRegion_;
  QLabel *finalSizeLabel_;

public:

  explicit DestinationModeRegion( QWidget *parent ,
                                  SelectionArea *selectionArea ,
                                  const RSWParameters& parameters );

  bool isFixedMode( ) const;

  QSize getFixedSize( ) const;

  QSizeF getScaledSize( ) const;

public slots:

  void refreshRegion( );

  void refreshOutputSize( );

};


#endif //QTRECORDER_DESTINATIONMODEREGION_H
