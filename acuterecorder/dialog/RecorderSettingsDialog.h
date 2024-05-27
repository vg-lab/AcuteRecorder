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
