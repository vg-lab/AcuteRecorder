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

#ifndef ACUTERECORDER_RECORDERSTORAGEWORKER_H
#define ACUTERECORDER_RECORDERSTORAGEWORKER_H

#include <QThread>
#include <acuterecorder/api.h>
#include <memory>

class QObject;
class QSize;
class QImage;

/**
 * A storage worker that receives frames and storages them in some way.
 *
 * Default implementations of this class are:
 * - FFMPEGRecorderStorageWorker (Builder name: ffmpeg)
 * - ImageRecorderStorageWorker (Builder name: image)
 */
class ACUTERECORDER_API RecorderStorageWorker : public QThread
{

Q_OBJECT

protected:

  /**
   * Starts the worker.
   * This method does nothing if the worker is already running.
   */
  void run( ) override;

  QString error_; /** error message or empty if success. */

public:

  explicit RecorderStorageWorker( QObject *parent );

  /**
   * Sends a frame to the storage.
   * @param image the frame.
   */
  virtual void push( std::shared_ptr<QImage> image );

  /** \brief Returns the error message or empty if success.
   *
   */
  QString errorMessage() const
  { return error_; }

public slots:

  /**
   * Stops the worker.
   * This method does nothing if the worker is not running.
   */
  virtual void stop( );

signals:

  /**
   * Notifies a change in the buffer of the worker.
   * @param size the size of the buffer.
   */
  void fileQueueSizeChanged( int size );

  void error(const QString &message);

};


#endif //ACUTERECORDER_RECORDERSTORAGEWORKER_H
