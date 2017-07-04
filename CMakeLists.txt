# Set the minimum CMake version
cmake_minimum_required (VERSION 2.6)

# Set the project name
set (PROJECT_NAME "Asteroids")

# Name the CMake project
project (${PROJECT_NAME})

# Set flags
set (CMAKE_CXX_FLAGS "-Wall -std=c++17")

# Add the headers
include_directories(include)

# Set the GLOB command to search for all source and header files in the src directory
file (GLOB SOURCE_FILES src/*.cpp)

file(COPY ${CMAKE_SOURCE_DIR}/Resources DESTINATION ${PROJECT_BINARY_DIR})

# Find the required packages
find_package (SFML REQUIRED system window graphics network audio)

# Include the package directories
include_directories(${SFML_INCLUDE_DIRS})

# Create the executable
add_executable (${PROJECT_NAME} ${SOURCE_FILES})

# Link libraries
target_link_libraries (${PROJECT_NAME} ${SFML_LIBRARIES})