cmake_minimum_required(VERSION 3.5)

# Set the project name
project (Game)

find_package(SDL2 REQUIRED)

# Create a sources variable with a link to all cpp files to compile
#set(SOURCES
#    ./src/*.cpp
#)

file (GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

# Add an executable with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

# Set the directories that should be included in the build command for this target
include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})