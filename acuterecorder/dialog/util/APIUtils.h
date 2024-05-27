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

#ifndef QTRECORDER_UTILS_H
#define QTRECORDER_UTILS_H

#include <QWidget>

class RecorderSettings;

namespace api_utils
{

  /**
   * Finds the deepest subwidget whose area contains the given point.
   * @param parent the root widget.
   * @param point the point.
   * @param ignore the algorithm will ignore this widget.
   * @return the child. If no child is found,
   * this method returns the given parent.
   */
  QWidget *findDeepestChildWithPoint( QWidget *parent ,
                                      const QPoint& point ,
                                      QWidget *ignore = nullptr );

  /**
   * Validates the given RecorderSettings.
   * This method also searches for file overwrites.
   * @param parent the parent of the dialogs. Can be nullptr.
   * @param settings the settings to validate.
   * @param folderMode whether the selected worker is a folder mode worker.
   * @return whether the RecorderSettings is valid.
   */
  bool validateSettings( QWidget *parent ,
                         const RecorderSettings& settings ,
                         const bool folderMode );
}

#endif //QTRECORDER_UTILS_H
