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

#ifndef ACUTERECORDER_FFMPEGSTORAGETHREAD_H
#define ACUTERECORDER_FFMPEGSTORAGETHREAD_H


#include <QObject>
#include <QSize>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QThread>

#include "RecorderStorageWorker.h"
#include "RecorderSettings.h"

class QImage;

/**
 * This worker encodes the frames to a video using FFMPEG.
 */
class FFMPEGRecorderStorageWorker : public RecorderStorageWorker
{

Q_OBJECT

  QSize size_;
  int fps_;
  QString output_;
  QStringList codecs_;

  qint64 expectedBytesPerLine_;

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
  bool popElement( std::shared_ptr< QImage >& image );

protected:

  void run( ) override;

public:

  /**
   * Creates the storage worker.
   * @param size the size of each frame.
   * @param fps the FPS of the video.
   * @param output the output path of the video.
   */
  FFMPEGRecorderStorageWorker( QObject *object ,
                               const RecorderSettings &settings );

  virtual void push( std::shared_ptr< QImage > image ) override;

  static const QString CODECS_KEY;

public slots:

  virtual void stop( ) override;

};


#endif //ACUTERECORDER_FFMPEGSTORAGETHREAD_H
