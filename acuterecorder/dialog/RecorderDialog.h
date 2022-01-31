//
// Created by gaelr on 18/01/2022.
//

#ifndef ACUTERECORDER_RECORDERDIALOG_H
#define ACUTERECORDER_RECORDERDIALOG_H

#include <acuterecorder/api.h>

#include <QDialog>

class RecorderSettingsWidget;

class Recorder;

class QDialogButtonBox;

struct RSWParameters;

/**
 * Useful dialog for creating a Recorder.
 *
 * Execute an instance of this dialog. If the result is QDialog::Accepted (1),
 * a new Recorder was created. You can access this Recorder using
 * RecorderDialog::getRecorder().
 *
 */
class ACUTERECORDER_API RecorderDialog : public QDialog
{

Q_OBJECT

private:

  Recorder *recorder_;

  bool takeFramesAutomatically_;

  RecorderSettingsWidget *settingsWidget_;

public:

  /**
   * Creates the dialog.
   * @param parent the parent of the widget.
   * @param root the widget to record.
   * @param includeScreens if the screen combobox should include the screens.
   * @param takeFramesAutomatically whether a QTimer should be
   * created to take frames automatically based on the defined FPS.
   */
  RecorderDialog( QWidget *parent ,
                  const RSWParameters& parameters ,
                  bool takeFramesAutomatically );

  /**
   * If the dialog was executed and the result is QDialog::Accepted (or 1),
   * this method returns the created recorder. Otherwise, this method
   * returns nullptr.
   * @return the recorder or nullptr.
   */
  Recorder *getRecorder( );


private slots:

  void tryToAccept( );

};


#endif //ACUTERECORDER_RECORDERDIALOG_H
