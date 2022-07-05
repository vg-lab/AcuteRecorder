//
// Created by gaeqs on 12/15/21.
//

#include <worker/FFMPEGRecorderStorageWorker.h>
#include <RecorderSettings.h>

#include <QProcess>

#include "FFMPEGWorkerBuilder.h"

FFMPEGWorkerBuilder::FFMPEGWorkerBuilder( )
: WorkerBuilder( false )
{ }

bool FFMPEGWorkerBuilder::isAvailable( ) const
{
  QProcess process;
  process.start("ffmpeg",
                QStringList{"-hide_banner", "-codecs"},
                QIODevice::OpenMode::enum_type::ReadWrite);
  process.waitForFinished( );

  if ( process.exitCode( ) != 0 ) return false;

  const auto output = process.readAllStandardOutput( );

  codecs.clear();

  // valid detected codecs
  if(output.contains( "h264_nvenc" )) codecs << "h264_nvenc";
  if(output.contains( "h264_vaapi" )) codecs << "h264_vaapi";
  if(output.contains( "libx264" ))    codecs << "libx264";
  if(output.contains( "mpeg4" ))      codecs << "mpeg4";

  return !codecs.isEmpty();
}

RecorderStorageWorker *FFMPEGWorkerBuilder::createWorker(
  QObject *object , RecorderSettings& settings ) const
{
  settings.setExtraSetting(FFMPEGRecorderStorageWorker::CODECS_KEY, codecs);

  return new FFMPEGRecorderStorageWorker( object , settings);
}
