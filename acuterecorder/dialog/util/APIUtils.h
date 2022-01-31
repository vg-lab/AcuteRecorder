//
// Created by Gael Rial Costas on 16/8/21.
//
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
