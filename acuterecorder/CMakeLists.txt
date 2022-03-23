set(PROJECT_VERSION_ABI ${${PROJECT_NAME}_VERSION_ABI})

set(Name AcuteRecorder)
set(NAME ACUTERECORDER)
set(namespace acuterecorder)
set(NAMESPACE ACUTERECORDER)
set(INCLUDE_NAME acuterecorder)
configure_file(${CMAKE_SOURCE_DIR}/CMake/common/cpp/api.h
        ${PROJECT_BINARY_DIR}/include/acuterecorder/api.h @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/CMake/common/cpp/version.h
        ${PROJECT_BINARY_DIR}/include/acuterecorder/version.h @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/CMake/common/cpp/version.cpp
        ${PROJECT_BINARY_DIR}/src/acuterecorder/version.cpp @ONLY)

#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR}/include)

set(ACUTERECORDER_SOURCES
        Input.cpp
        RecorderSettings.cpp
        Recorder.cpp
        worker/RecorderStorageWorker.cpp
        worker/FFMPEGRecorderStorageWorker.cpp
        worker/ImageRecorderStorageWorker.cpp
        worker/WorkerBuilder.cpp
        worker/FFMPEGWorkerBuilder.cpp
        worker/ImageWorkerBuilder.cpp
        dialog/element/ScreenComboBox.cpp
        dialog/element/SelectionArea.cpp
        dialog/region/DestinationModeRegion.cpp
        dialog/region/FixedDestinationModeRegion.cpp
        dialog/region/OutputRegion.cpp
        dialog/region/ScaledDestinationModeRegion.cpp
        dialog/region/SelectionModeRegion.cpp
        dialog/util/PixmapHolder.cpp
        dialog/util/APIUtils.cpp
        dialog/RecorderDialog.cpp
        dialog/RecorderSettingsDialog.cpp
        dialog/RecorderSettingsWidget.cpp
        )

set(ACUTERECORDER_PUBLIC_HEADERS
        ${PROJECT_BINARY_DIR}/include/acuterecorder/version.h
        Input.h
        RecorderSettings.h
        Recorder.h
        worker/RecorderStorageWorker.h
        worker/WorkerBuilder.h
        dialog/constant/Styles.h
        dialog/element/ScreenComboBox.h
        dialog/element/SelectionArea.h
        dialog/util/PixmapHolder.h
        dialog/RecorderDialog.h
        dialog/RecorderSettingsDialog.h
        dialog/RecorderSettingsWidget.h
        dialog/RSWParameters.h
        )

set(ACUTERECORDER_HEADERS
        )

set(ACUTERECORDER_LINK_LIBRARIES
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets)

set(ACUTERECORDER_INCLUDE_NAME acuterecorder)
set(ACUTERECORDER_NAMESPACE acuterecorder)
add_definitions(-DACUTERECORDER_SHARED)
common_library(acuterecorder)

