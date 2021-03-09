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
        src/MyRubberWindow.cpp
        src/MyRubberWindow.h
        src/RenderManager.cpp
        src/RenderManager.h
        src/StoreManager.cpp
        src/StoreManager.h)


target_link_libraries(QtRecorder Qt5::Widgets)

# Qt Style file
configure_file(resources/style.css ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)