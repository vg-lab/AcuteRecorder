cmake_minimum_required(VERSION 3.16.3)
project(QtRecorder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(RECORDER_SOURCES
        src/main.cpp
        src/render/WidgetRenderThread.cpp
        src/render/VideoStorageThread.cpp
        src/render/AbstractRendererThread.cpp
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
        src/render/QRenderHelper.cpp
        src/util/PixmapHolder.cpp
        src/element/SelectionArea.cpp)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/src)

qt5_add_resources(RECORDER_SOURCES resources/resources_index.qrc)
add_executable(QtRecorder ${RECORDER_SOURCES})
target_link_libraries(QtRecorder Qt5::Widgets)