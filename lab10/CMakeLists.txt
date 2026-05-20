cmake_minimum_required(VERSION 3.10)
project(program)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

include_directories(include)

file(GLOB_RECURSE LIB_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library(configlib STATIC ${LIB_SOURCES})

add_executable(program ${PROJECT_SOURCE_DIR}/src/Main.cpp)
target_link_libraries(program configlib)