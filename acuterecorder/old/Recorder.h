//
// Created by gaelr on 16/11/2021.
//

#ifndef ACUTERECORDER_ACUTERECORDER_H
#define ACUTERECORDER_ACUTERECORDER_H

struct RecorderGeneralData;

namespace acute_recorder
{

  /**
   * Starts recording a video using the information in the
   * given RecorderGeneralData.
   *
   * This function returns false if the given RecorderGeneralData
   * is already being used to record another video.
   *
   * @param data the data.
   * @return whether the operation was successful.
   */
  bool start_recording( RecorderGeneralData *data );

  /**
   * Stops the recording linked to the given RecorderGeneralData.
   * After an invocation of this function,
   * the given RecorderGeneralData is free to be reused.
   *
   * This function returns false if the given RecorderGeneralData
   * is not being used to record any video.
   *
   * @param data the data.
   * @return whether the operation was successful.
   */
  bool stop_recording( RecorderGeneralData *data );

}

#endif //ACUTERECORDER_ACUTERECORDER_H
