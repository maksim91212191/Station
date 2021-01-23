cmake_minimum_required(VERSION 2.6)
project(stationmain)

set(EXEC_TARGET ${CMAKE_PROJECT_NAME})
set(CMAKE_VERBOSE_MAKEFILE OFF)

file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/Bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Include)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DDEBUG)
  file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/Bin/tmp)
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/../ ${CMAKE_BINARY_DIR}/station)
add_subdirectory(${CMAKE_SOURCE_DIR}/../../BME280 ${CMAKE_BINARY_DIR}/bme)

set(SOURCES ${SOURCES}
  ./Source/main.cpp
  )

#set(HEADERS)

add_executable(${EXEC_TARGET} ${SOURCES} ${HEADERS})

target_link_libraries(${EXEC_TARGET}
  station${PLATFORM_EXEC_SUFFIX}
  bme${PLATFORM_EXEC_SUFFIX}
  pthread
  rt
  dl
  )

install (TARGETS ${EXEC_TARGET} DESTINATION Bin)
