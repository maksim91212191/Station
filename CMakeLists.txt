cmake_minimum_required(VERSION 3.0)
project(station)

set(LIB_TARGET ${PROJECT_NAME}${PLATFORM_EXEC_SUFFIX})

set(SOURCES
  ./Source/station.cpp
  )

# set(HEADERS
#   )

add_definitions(-lwiringPi)

add_library(${LIB_TARGET} ${SOURCES} ${HEADERS})

target_include_directories(${LIB_TARGET}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Include/${PROJECT_NAME})

target_compile_definitions(${LIB_TARGET} PUBLIC TMS320C66X)

target_link_libraries(${LIB_TARGET}
  bme${PLATFORM_EXEC_SUFFIX}
  )

# target_add_ide_support(${LIB_TARGET})
