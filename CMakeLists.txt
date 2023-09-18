# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#   Acute Recorder
#   2021-2021 (c) Acute Recorder / Universidad Rey Juan Carlos
#   g.rial.2018@alumnos.urjc.es
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

cmake_minimum_required( VERSION 3.1 FATAL_ERROR )

# project and version
project( acuterecorder VERSION 1.0.5 )
set( acuterecorder_VERSION_ABI 1 )

SET( acuterecorder_LICENSE "GPL")

# Disable in source building
if( "${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}" )
  message( FATAL "no in source building allowed.")
endif()

list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake
                               ${CMAKE_SOURCE_DIR}/CMake/common )

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/CMake/common/Common.cmake)
  message(FATAL_ERROR "CMake/common missing, run: git submodule update --init")
endif()

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug )
endif( NOT CMAKE_BUILD_TYPE )

if( CMAKE_BUILD_TYPE MATCHES "Debug" )
  add_definitions(-DDEBUG)
endif()

include(GitExternal)

# description
set(acuterecorder_DESCRIPTION "Acute Recorder")
set(COMMON_PROJECT_DOMAIN vg-lab.es)

# this forces C++11
include(Common)

option(BUILD_EXAMPLE "BUILD ACUTE RECORDER EXAMPLE" ON)

common_find_package( Qt5Core 5.4 REQUIRED )
common_find_package( Qt5Gui 5.4 REQUIRED )
common_find_package( Qt5Widgets 5.4 REQUIRED )

list( APPEND ACUTERECODER_DEPENDENT_LIBRARIES
  Qt5Core
  Qt5Gui
  Qt5Widgets
)

common_find_package_post()

add_subdirectory( acuterecorder )

if(BUILD_EXAMPLE)
	add_subdirectory( example )
endif()

include( CPackConfig )
include( DoxygenRule )
