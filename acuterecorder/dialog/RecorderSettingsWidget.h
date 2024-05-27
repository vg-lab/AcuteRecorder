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

#ifndef QTRECORDER_SETTINGSWIDGET_H
#define QTRECORDER_SETTINGSWIDGET_H

#include <acuterecorder/api.h>
#include <acuterecorder/RecorderSettings.h>

#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>

class SelectionArea;

class ScreenComboBox;

class SelectionModeRegion;

class DestinationModeRegion;

class OutputRegion;

class StartStopButton;

class QProgressBar;

struct RSWParameters;

/**
 * Helper widget, useful for creating RecorderSettings.
 */
class ACUTERECORDER_API RecorderSettingsWidget : public QWidget
{

Q_OBJECT

  SelectionArea *selectionArea_;
  ScreenComboBox *screenComboBox_;
  SelectionModeRegion *selectionModeRegion_;
  DestinationModeRegion *destinationModeRegion_;
  OutputRegion *outputRegion_;

  bool stabilizeFramerate_;

public:

  /**
   * Creates the helper widget.
   * @param parent the parent of the widget.
   * @param root the widget to record.
   */
  RecorderSettingsWidget( QWidget *parent ,
                          const RSWParameters& parameters );

  /**
   * Returns the RecorderSettings configured by this helper widget.
   * @return the RecorderSettings.
   */
  RecorderSettings getSettings( );

  /**
   * Returns whether the selected worker targets a folder instead a file.
   *
   * This method is useful if you want to check if the file already exists
   * without having to fetch the worker builder.
   *
   * @return whether the selected worker targets a folder instead a file.
   */
  bool isFolderMode( );
};


#endif //QTRECORDER_SETTINGSWIDGET_H
