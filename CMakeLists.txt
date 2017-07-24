# Set the minimum CMake version
cmake_minimum_required (VERSION 2.6)

# Set the project name
set (PROJECT_NAME "Asteroids")

# Get the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Name the CMake project
project (${PROJECT_NAME})

# Set flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -std=c++17")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -std=c++17")

# Add the headers
include_directories(include)

# Set the source files
set (SOURCE_FILES
        src/Asteroid.cpp
        src/AsteroidsGame.cpp
        src/Entity.cpp
        src/GeoMaths.cpp
        src/MainWindow.cpp
        src/Missile.cpp
        src/ScoreKeeper.cpp
        src/Ship.cpp
        src/AudioController.cpp
        )

file(COPY ${CMAKE_SOURCE_DIR}/Resources DESTINATION ${PROJECT_BINARY_DIR})

# Add local Cmake modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Find the required packages
find_package (SFML 2 REQUIRED system window graphics network audio)

# Use static libs if specified
if(SFML_STATIC_LIBS)
    set(SFML_STATIC_LIBRARIES TRUE)
endif()

# Include the package directories
include_directories(${SFML_INCLUDE_DIRS})

# Create the executable
add_executable (${PROJECT_NAME} ${SOURCE_FILES})

# Link libraries
target_link_libraries (${PROJECT_NAME} ${SFML_LIBRARIES})
