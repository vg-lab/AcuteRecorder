cmake_minimum_required(VERSION 3.17)
project(QtRecorder)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(QtRecorder
        src/main.cpp
        src/element/SelectionArea.cpp
        src/element/SelectionArea.h
        src/render/WidgetRenderThread.cpp
        src/render/WidgetRenderThread.h
        src/render/VideoStorageThread.cpp
        src/render/VideoStorageThread.h
        src/render/AbstractRendererThread.cpp
        src/render/AbstractRendererThread.h
        src/element/QueueSizeBar.cpp
        src/element/QueueSizeBar.h
        src/region/MainWindowRegion.cpp
        src/region/MainWindowRegion.h
        src/data/RecorderGeneralData.h
        src/element/OutputTextField.cpp
        src/element/OutputTextField.h
        src/constant/Styles.h
        src/region/SelectionModeRegion.cpp
        src/region/SelectionModeRegion.h
        src/element/SelectionModeButton.cpp
        src/element/SelectionModeButton.h
        src/constant/QtUtils.h
        src/element/StartStopButton.cpp
        src/element/StartStopButton.h
        src/data/ViewportI.h
        src/data/ViewportD.h
        src/element/DestinationModeButton.cpp
        src/element/DestinationModeButton.h
        src/region/DestinationModeRegion.cpp
        src/region/DestinationModeRegion.h
        src/region/FixedDestinationModeRegion.cpp
        src/region/FixedDestinationModeRegion.h
        src/region/ScaledDestinationModeRegion.cpp
        src/region/ScaledDestinationModeRegion.h
        src/region/OutputRegion.cpp
        src/region/OutputRegion.h
        src/element/OutputFileButton.cpp
        src/element/OutputFileButton.h
        src/constant/QTUtils.cpp src/element/FPSTextField.cpp src/element/FPSTextField.h src/element/ScreenComboBox.cpp src/element/ScreenComboBox.h src/render/QRenderHelper.cpp src/render/QRenderHelper.h)


target_link_libraries(QtRecorder Qt5::Widgets)

# Qt Style file
configure_file(resources/style.css ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)