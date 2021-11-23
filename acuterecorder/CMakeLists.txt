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
        RecorderSettingsBuilder.cpp
        Recorder.cpp
        RecorderStorageWorker.cpp
        )

set(ACUTERECORDER_PUBLIC_HEADERS
        ${PROJECT_BINARY_DIR}/include/acuterecorder/version.h
        Input.h
        RecorderSettings.h
        RecorderSettingsBuilder.h
        Recorder.h
        RecorderStorageWorker.h
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

