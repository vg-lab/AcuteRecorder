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
  process.start( "ffmpeg" ,
                 QStringList( "-codecs" ) ,
                 QIODevice::OpenMode::enum_type::ReadWrite
  );
  process.waitForFinished( );

  if ( process.exitCode( ) != 0 ) return false;

  const auto output = process.readAllStandardOutput( );
  return output.contains( "nvenc_h264" );
}


RecorderStorageWorker *FFMPEGWorkerBuilder::createWorker(
  QObject *object , const RecorderSettings& settings ) const
{
  return new FFMPEGRecorderStorageWorker( object ,
                                          settings.getOutputSize( ) ,
                                          settings.getFPS( ) ,
                                          settings.getOutputPath( ));
}
