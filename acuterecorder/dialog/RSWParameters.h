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

#ifndef ACUTERECORDER_RSWPARAMETERS_H
#define ACUTERECORDER_RSWPARAMETERS_H

#include <acuterecorder/api.h>
#include <acuterecorder/dialog/util/SelectionMode.h>

#include <vector>
#include <utility>

#include <QString>

class QWidget;

/**
 * Build parameters of a RecorderSettingsWidget.
 * Use this struct to configure the widget.
 */
struct ACUTERECORDER_API RSWParameters
{

  // INPUT SECTION

  /**
   * The widgets present in the source combo box.
   * The user may select one of these and use it to record.
   */
  std::vector< std::pair< QString, QWidget * > > widgetsToRecord;

  /**
   * Add the computer's screens into the source combo box.
   * The user may select one of these and use it to record.
   */
  bool includeScreens = true;

  // SOURCE AREA SECTION

  /**
   * Makes the source section of the widget visible.
   * If false, the buttons full, area and widget will be hidden.
   */
  bool showSourceParameters = true;

  /**
   * Makes visible the source's full button.
   */
  bool showFullSourceMode = true;

  /**
   * Makes visible the source's area button.
   */
  bool showAreaSourceMode = true;

  /**
 * Makes visible the source's widget button.
 */
  bool showWidgetSourceMode = true;

  /**
   * The default selected source button of all three.
   */
  SelectionMode defaultSelectionMode = SelectionMode::FULL;

  /**
   * Makes the FPS area visible.
   */
  bool showFPS = true;

  /**
   * The default FPS amount.
   */
  int defaultFPS = 60;

  /**
   * Makes the output area section visible.
   */
  bool showOutputSizeParameters = true;

  /**
   * If true, the scaled output area option is selected.
   * If false, the fixed output area option is selected.
   */
  bool defaultOutputSizeScaled = true;

  /**
   * The default value of the fixed output area.
   */
  QSize defaultFixedOutputSize = QSize( 1920 , 1080 );

  /**
   * The default value of the scaled output area.
   */
  QSizeF defaultScaledOutputSize = QSizeF( 1.0f , 1.0f );

  /**
   * Makes the output path section visible.
   */
  bool showOutput = true;

  /**
   * The default output path value.
   */
  QString defaultOutput = "output.mkv";

  /**
   * Makes the worker combo box visible.
   */
  bool showWorker = true;

  /**
   * The default worker.
   */
  QString defaultWorker = "ffmpeg";

  /**
   * Whether the created settings must have the framerate stabilizer
   * activated by default.
   */
  bool stabilizeFramerate = false;
};

#endif //ACUTERECORDER_RSWPARAMETERS_H
