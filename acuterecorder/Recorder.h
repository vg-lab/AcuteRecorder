//
// Created by gaelr on 18/11/2021.
//

#ifndef ACUTERECORDER_RECORDER_H
#define ACUTERECORDER_RECORDER_H


#include <QObject>
#include "RecorderSettings.h"
#include "RecorderStorageWorker.h"

class RecorderSettings;

class Recorder : public QObject
{

Q_OBJECT

  RecorderSettings settings_;
  bool active_;
  RecorderStorageWorker storageWorker_;

public:

  explicit Recorder( RecorderSettings settings );

  bool isRecording( ) const;

public slots:

  void takeFrame( );

  void stop( );

signals:

  void bufferSizeChange( int value );

  void finished( );

};


#endif //ACUTERECORDER_RECORDER_H
