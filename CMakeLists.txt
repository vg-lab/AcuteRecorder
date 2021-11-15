cmake_minimum_required(VERSION 3.16.3)

project(QtRecorderLib VERSION 1.0.0 DESCRIPTION "QtRecorder LIB")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(qtrecorderlib/include)
add_library(QtRecorderLib SHARED
        qtrecorderlib/src/WidgetRenderThread.cpp
        qtrecorderlib/src/VideoStorageThread.cpp
        qtrecorderlib/src/AbstractRendererThread.cpp
        qtrecorderlib/src/QRenderHelper.cpp)

target_link_libraries(QtRecorderLib Qt5::Widgets)

project(QtRecorder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(RECORDER_SOURCES
        src/main.cpp
        src/element/QueueSizeBar.cpp
        src/region/MainWindowRegion.cpp
        src/element/OutputTextField.cpp
        src/region/SelectionModeRegion.cpp
        src/element/SelectionModeButton.cpp
        src/element/StartStopButton.cpp
        src/element/DestinationModeButton.cpp
        src/region/DestinationModeRegion.cpp
        src/region/FixedDestinationModeRegion.cpp
        src/region/ScaledDestinationModeRegion.cpp
        src/region/OutputRegion.cpp
        src/element/OutputFileButton.cpp
        src/util/QtUtils.cpp
        src/element/FPSTextField.cpp
        src/element/ScreenComboBox.cpp
        src/util/PixmapHolder.cpp
        src/element/SelectionArea.cpp)

include_directories(${CMAKE_SOURCE_DIR}/src)
qt5_add_resources(RECORDER_SOURCES resources/resources_index.qrc)
add_executable(QtRecorder ${RECORDER_SOURCES})
target_link_libraries(QtRecorder QtRecorderLib)
# target_link_libraries(QtRecorder Qt5::Widgets) No needed? Already linked in QtRecorderLib?
