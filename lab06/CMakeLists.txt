cmake_minimum_required(VERSION 3.5.0)
project (Logger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DPROJECTPATH=\"${PROJECT_SOURCE_DIR}\")

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

set(CMAKE_CXX_FLAGST "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(${PROJECT_SOURCE_DIR}/include)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
else()
  set(CMAKE_BUILD_TYPE "Release")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -DNDEBUG")
endif()

add_library(configlib STATIC 
    ${PROJECT_SOURCE_DIR}/src/Logger.cpp 
)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/Main.cpp
)

add_executable(program ${SOURCES})

target_include_directories(program PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(program PUBLIC configlib)