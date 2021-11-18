//
// Created by gaelr on 16/11/2021.
//

#include <acuterecorder/RecorderGeneralData.h>
#include <acuterecorder/WidgetRenderThread.h>
#include <Recorder.h>

namespace acute_recorder
{
  bool start_recording( RecorderGeneralData *data )
  {
    if ( data->isRecording( )) return false;
    data->thread = std::make_shared<WidgetRenderThread>( data );
    data->thread->start( );
    return true;
  }

  bool stop_recording( RecorderGeneralData *data )
  {
    if ( !data->isRecording( )) return false;
    data->thread->stop( );
    data->thread->storeManager( )->join( );
    data->thread = nullptr;
    return true;
  }
}
