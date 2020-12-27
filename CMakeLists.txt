cmake_minimum_required(VERSION 3.0)
project(station)

set(LIB_TARGET ${PROJECT_NAME}${PLATFORM_EXEC_SUFFIX})

set(SOURCES
  ./Source/bme280.cpp
  )

set(HEADERS
  ./Include/station/BME280/bme280.h
  ./Include/station/BME280/BME280CalibrationData.h
  ./Include/station/BME280/BME280Data.h
  ./Include/station/BME280/BME280RawData.h
  )

add_definitions(-lwiringPi)

add_library(${LIB_TARGET} ${SOURCES} ${HEADERS})

target_include_directories(${LIB_TARGET}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Include/${PROJECT_NAME})

target_compile_definitions(${LIB_TARGET} PUBLIC TMS320C66X)

# target_add_ide_support(${LIB_TARGET})
