cmake_minimum_required(VERSION 3.5)
project(QuestProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SRC_QUEST
    ${PROJECT_SOURCE_DIR}/src/Quest.cpp
)

add_library(quest STATIC ${SRC_QUEST})

set(SRC_MAIN
    ${PROJECT_SOURCE_DIR}/src/Main.cpp
)

add_executable(program ${SRC_MAIN})
target_link_libraries(program PRIVATE quest)