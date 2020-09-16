cmake_minimum_required(VERSION 3.7)
project(2dGame)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(2dGame src/*.cpp)
target_link_libraries(2dGame ${SDL2_LIBRARIES})