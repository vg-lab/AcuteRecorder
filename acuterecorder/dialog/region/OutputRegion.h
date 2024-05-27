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

#ifndef QTRECORDER_OUTPUTREGION_H
#define QTRECORDER_OUTPUTREGION_H

#include <QWidget>
#include <QString>

class QLineEdit;

class QComboBox;

class WorkerBuilder;

struct RSWParameters;

class OutputRegion : public QWidget
{
Q_OBJECT

  QLineEdit *outputTextField_;
  QComboBox *workers_;
  bool folderMode_;
  QString defaultOutput_;

public:

  explicit OutputRegion( QWidget *parent , const RSWParameters& parameters );

  QString getOutputPath( ) const;

  QString getWorkerName( ) const;

  bool isFolderMode( ) const;

private slots:

  void openFileOrFolderDialog( );

  void openFileDialog( );

  void openFolderDialog( );

  void changeFolderMode( const QString& worker );

};


#endif //QTRECORDER_OUTPUTREGION_H
