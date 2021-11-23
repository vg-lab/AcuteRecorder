set(RECORDER_SOURCES
        main.cpp
		element/StartStopButton.cpp
		element/ScreenComboBox.cpp
		element/SelectionArea.cpp
        region/MainWindowRegion.cpp
        region/SelectionModeRegion.cpp
        region/DestinationModeRegion.cpp
        region/FixedDestinationModeRegion.cpp
        region/ScaledDestinationModeRegion.cpp
        region/OutputRegion.cpp
        util/QtUtils.cpp
        util/PixmapHolder.cpp
		resources/resources_index.qrc)

set(RECORDER_HEADERS
		element/StartStopButton.h
		element/ScreenComboBox.h
		element/SelectionArea.h
		region/MainWindowRegion.h
		region/DestinationModeRegion.h
		region/FixedDestinationModeRegion.h
		region/ScaledDestinationModeRegion.h
		region/OutputRegion.h
		util/QtUtils.h
		util/PixmapHolder.h
		util/SelectionMode.h)
		
include_directories(${CMAKE_CURRENT_SOURCE_DIR})		
include_directories(${ACUTERECORDER_INCLUDE_DIR})

set(RECORDER_LINK_LIBRARIES
	acuterecorder )

common_application(recorder GUI ${COMMON_APP_ARGS})
