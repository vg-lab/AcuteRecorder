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

#ifndef QTRECORDER_STYLES_H
#define QTRECORDER_STYLES_H

#include <acuterecorder/api.h>

#include <QString>

namespace styles
{
  const QString OUTPUT_TEXT_FIELD = "output-text-field";
  const QString OUTPUT_FILE_BUTTON = "output-file-button";
  const QString INFO_LABEL = "info-label";
  const QString SUB_INFO_LABEL = "sub-info-label";
  const QString SECONDARY_INFO_LABEL = "secondary-info-label";
  const QString FIXED_WIDTH = "fixed-width";
  const QString FIXED_HEIGHT = "fixed-height";
  const QString SCALED_WIDTH = "scaled-width";
  const QString SCALED_HEIGHT = "scaled-height";
  const QString FPS = "fps";
  const QString WORKERS = "workers";

  const QString SELECTION_RADIO_BUTTON = "selection-radio-button";
  const QString DESTINATION_RADIO_BUTTON = "destination-radio-button";

  const QString REGION_SETTINGS_WIDGET = "region-settings-widget";
  const QString REGION_SELECTION_MODE = "region-selection-mode";
  const QString REGION_DESTINATION_MODE = "region-destination-mode";
  const QString REGION_FIXED_DESTINATION_MODE = "region-fixed-destination-mode";
  const QString REGION_SCALED_DESTINATION_MODE = "region-scaled-destination-mode";
  const QString REGION_OUTPUT = "region-output";
}

#endif //QTRECORDER_STYLES_H
