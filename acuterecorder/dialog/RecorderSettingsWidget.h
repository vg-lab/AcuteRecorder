//
// Created by Gael Rial Costas on 16/8/21.
//

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
