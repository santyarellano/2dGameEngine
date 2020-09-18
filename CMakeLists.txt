cmake_minimum_required(VERSION 3.5)

# Set the project name
project (Game)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_ttf REQUIRED)

find_package(SDL2_image REQUIRED)

# Create a sources variable with a link to all cpp files to compile
#set(SOURCES
#    ./src/*.cpp
#)

file(GLOB_RECURSE src_list ${CMAKE_SOURCE_DIR} "src/*.cpp")

# Add an executable with the above sources
add_executable(${PROJECT_NAME} ${src_list})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

# Set the directories that should be included in the build command for this target
#include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})