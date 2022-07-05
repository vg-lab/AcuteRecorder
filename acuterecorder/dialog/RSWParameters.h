//
// Created by gaelr on 21/01/2022.
//

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
