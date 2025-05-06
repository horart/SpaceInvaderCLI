cmake_minimum_required(VERSION 3.5)
project(SpaceInvader)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

find_package(Curses REQUIRED)
include_directories(${NCURSES_INCLUDE_DIRS})


file(GLOB ENGINE_SOURCE engine/src/*.cpp)
add_library(Engine ${ENGINE_SOURCE})
target_link_libraries(Engine ${NCURSES_LIBRARIES})
target_include_directories(Engine PUBLIC engine/src/template)

include_directories(engine/include)

include_directories(include)



file(GLOB SOURCE src/*.cpp)
add_executable(SpaceInvader ${SOURCE})

target_link_libraries(SpaceInvader Engine)