set(RECORDER_SOURCES
        main.cpp
        element/StartStopButton.cpp
        region/MainWindowRegion.cpp
        util/QtUtils.cpp
        resources/resources_index.qrc)

set(RECORDER_HEADERS
        constant/Styles.h
        element/StartStopButton.h
        region/MainWindowRegion.h
        util/QtUtils.h
        )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${ACUTERECORDER_INCLUDE_DIR})

set(RECORDER_LINK_LIBRARIES
        acuterecorder)

common_application(recorder GUI ${COMMON_APP_ARGS})
