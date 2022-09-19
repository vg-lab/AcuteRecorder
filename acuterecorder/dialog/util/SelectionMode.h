//
// Created by Gael Rial Costas on 23/11/2021.
//

#ifndef ACUTERECORDER_SELECTIONMODE_H
#define ACUTERECORDER_SELECTIONMODE_H

#include <acuterecorder/api.h>

/**
 * The selection mode of a SelectionArea.
 */
enum class SelectionMode
{
  /**
   * This mode includes all the widget/screen into the viewport.
   */
  FULL = 0 ,
  /**
   * This mode only includes a selecting area into the viewport.
   */
  AREA ,
  /**
   * This mode only includes a subwidget into the viewport.
   */
  WIDGET
};

#endif //ACUTERECORDER_SELECTIONMODE_H
