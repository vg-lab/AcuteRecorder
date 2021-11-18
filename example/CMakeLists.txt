set(RECORDER_SOURCES
        main.cpp
        element/QueueSizeBar.cpp
        element/OutputTextField.cpp
		element/SelectionModeButton.cpp
		element/StartStopButton.cpp
		element/DestinationModeButton.cpp
		element/OutputFileButton.cpp
		element/FPSTextField.cpp
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
		element/QueueSizeBar.h
		element/OutputTextField.h
		element/SelectionModeButton.h
		element/StartStopButton.h
		element/DestinationModeButton.h
		element/OutputFileButton.h
		element/FPSTextField.h
		element/ScreenComboBox.h
		element/SelectionArea.h
		region/MainWindowRegion.h
		region/DestinationModeRegion.h
		region/FixedDestinationModeRegion.h
		region/ScaledDestinationModeRegion.h
		region/OutputRegion.h
		util/QtUtils.h
		util/PixmapHolder.h)
		
include_directories(${CMAKE_CURRENT_SOURCE_DIR})		
include_directories(${ACUTERECORDER_INCLUDE_DIR})

set(RECORDER_LINK_LIBRARIES
	acuterecorder )

common_application(recorder GUI ${COMMON_APP_ARGS})
