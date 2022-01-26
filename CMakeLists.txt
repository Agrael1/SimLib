# CMakeList.txt : CMake project for SimLib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

project ("SimLib" CXX)

set(CMAKE_CXX_STANDARD 23)

# include header files
include_directories(include)

# Add source to this project's executable.
add_library(${PROJECT_NAME} STATIC "include/SimObject.h" "include/TimeStats.h" "include/Stats.h"  "src/TimeStats.cpp" "src/Stats.cpp" "src/SimObject.cpp" "include/System.h" "include/Log.h" "src/Log.cpp" "include/Errors.h" "src/Errors.cpp")

ADD_CUSTOM_TARGET(
        auto_increment_version
        ${CMAKE_COMMAND}
        -D VERSION_FILE=${CMAKE_SOURCE_DIR}/include/version.h
        -P ${CMAKE_SOURCE_DIR}/AutoVersion.cmake
)
ADD_DEPENDENCIES(${PROJECT_NAME} auto_increment_version)
# TODO: Add tests and install targets if needed.
