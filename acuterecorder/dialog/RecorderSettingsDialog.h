//
// Created by gaelr on 18/01/2022.
//

#ifndef ACUTERECORDER_RECORDERSETTINGSDIALOG_H
#define ACUTERECORDER_RECORDERSETTINGSDIALOG_H

#include <acuterecorder/api.h>
#include <acuterecorder/RecorderSettings.h>

#include <QDialog>

class RecorderSettingsWidget;

class QDialogButtonBox;

struct RSWParameters;

/**
 * Useful dialog for creating a RecorderSettings.
 *
 * Execute an instance of this dialog. If the result is QDialog::Accepted (1),
 * a valid RecorderSettings can be fetched using
 * RecorderSettingsDialog::getSettings().
 *
 */
class ACUTERECORDER_API RecorderSettingsDialog : public QDialog
{

Q_OBJECT

private:

  RecorderSettingsWidget *settingsWidget_;

public:

  /**
   * Creates the dialog.
   * @param parent the parent of the widget.
   * @param root the widget to record.
   * @param includeScreens if the screen combobox should include the screens.
   */
  RecorderSettingsDialog( QWidget *parent ,
                          const RSWParameters& parameters );

  /**
   * Returns the RecorderSettings configured by this dialog.
   * @return the RecorderSettings.
   */
  RecorderSettings getSettings( );


private slots:

  void tryToAccept( );

};

#endif //ACUTERECORDER_RECORDERSETTINGSDIALOG_H
