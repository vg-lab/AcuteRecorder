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

#include <worker/FFMPEGRecorderStorageWorker.h>
#include <RecorderSettings.h>

#include <QProcess>

#include "FFMPEGWorkerBuilder.h"

#include <vector>
#include <string>

const std::vector<std::string> CODECS = {"h264_nvenc", "h264_amf", "h264_vaapi", "libx264", "mpeg4"};

FFMPEGWorkerBuilder::FFMPEGWorkerBuilder()
: WorkerBuilder(false)
{}

bool FFMPEGWorkerBuilder::isAvailable( ) const
{
  QByteArray ffmpeg_output;

  { // Destroy QProcess for the rest of the method.
    QProcess process;
    process.start("ffmpeg",
                  QStringList{"-hide_banner", "-codecs"},
                  QIODevice::OpenMode::enum_type::ReadWrite);
    process.waitForFinished();

    if (process.exitCode() != 0)
      return false;

    ffmpeg_output = process.readAllStandardOutput();
  }

  m_codecs.clear();

  for (const auto &codec : CODECS)
  {
    if (ffmpeg_output.contains(codec.c_str()) && isCodecSupportedByHardware(codec))
      m_codecs << QString::fromStdString(codec);
  }

  return !m_codecs.isEmpty();
}

RecorderStorageWorker *FFMPEGWorkerBuilder::createWorker(
  QObject *object , RecorderSettings& settings ) const
{
  settings.setExtraSetting(FFMPEGRecorderStorageWorker::CODECS_KEY, m_codecs);

  return new FFMPEGRecorderStorageWorker( object , settings);
}

bool FFMPEGWorkerBuilder::isCodecSupportedByHardware(const std::string &codec) const
{
  QProcess process;
  const QStringList parameters = {"-loglevel", "error", "-f", "lavfi", "-i", "color=black:s=1080x1080",
                                  "-vframes", "1", "-an", "-c:v", QString::fromStdString(codec), "-f", "null", "-"};
  process.start("ffmpeg", parameters, QIODevice::OpenMode::enum_type::ReadWrite);
  process.waitForFinished();

  if (process.exitCode() != 0)
    return false;

  return true;
}
