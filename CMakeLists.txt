cmake_minimum_required(VERSION 3.0)
project(station)

set(LIB_TARGET ${PROJECT_NAME}${PLATFORM_EXEC_SUFFIX})

set(SOURCES
  ./Source/station.cpp
  ./Source/server.cpp
  ./Source/managerRemote.cpp
  ./Source/analyzer.cpp
  )

 set(HEADERS
   ./Include/station/station.h
   ./Include/station/server.h
   ./Include/station/managerRemote.h
   ./Include/station/analyzer.h
   ./Include/station/resources.h
   )

find_library(wiringPi_LIB wiringPi)

set(Qt5_DIR "/usr/lib/arm-linux-gnueabihf/cmake/Qt5)"
find_package(Qt5 COMPONENTS Gui Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(${LIB_TARGET} ${SOURCES} ${HEADERS})

target_include_directories(${LIB_TARGET}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Include/station)

target_compile_definitions(${LIB_TARGET} PUBLIC TMS320C66X)

target_link_libraries(${LIB_TARGET}
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
  ${wiringPi_LIB}
  bme${PLATFORM_EXEC_SUFFIX}
  )
