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

#ifndef ACUTERECORDER_QTSTORAGETHREAD_H
#define ACUTERECORDER_QTSTORAGETHREAD_H


#include <QObject>
#include <QSize>
#include <QDir>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QThread>

#include "RecorderStorageWorker.h"

class QImage;

/**
 * This storage workers saves the frames in separate PNG files inside
 * a folder.
 */
class ImageRecorderStorageWorker : public RecorderStorageWorker
{

Q_OBJECT

  QDir output_;

  QMutex mutex_;
  QWaitCondition notEmptyCondition_;

  QQueue< std::shared_ptr< QImage > > queue_;
  volatile bool running_;

  /**
   * Pops an image from the queue. This method blocks the thread
   * until an image is found or the thread should end.
   *
   * If this second scenario occurs this method returns false.
   *
   * @param image the popped image.
   * @return whether the thread should continue.
   */
  bool popElement( std::shared_ptr<QImage>& image );

protected:

  void run( ) override;

public:

  /**
   * Creates the storage worker.
   * @param output the path of the output folder.
   */
  ImageRecorderStorageWorker( QObject *object , const QString &output );
  virtual ~ImageRecorderStorageWorker() {};

  virtual void push( std::shared_ptr< QImage > image ) override;

public slots:

  virtual void stop( ) override;

};


#endif //ACUTERECORDER_QTSTORAGETHREAD_H
