# CMakeList.txt : CMake project for SimLib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

project ("SimLib" CXX)

set(CMAKE_CXX_STANDARD 23)

# include header files
include_directories(include)

set(VERSION_FILE ${CMAKE_SOURCE_DIR}/include/version.h)

### Read version file ###
if(NOT EXISTS ${VERSION_FILE})
    file(CREATE ${VERSION_FILE})
endif()

add_executable(${PROJECT_NAME} "src/EntryMain.cpp" "include/Promises.h" "include/Version.h")

ADD_CUSTOM_TARGET(
        auto_increment_version
        ${CMAKE_COMMAND}
        -D VERSION_FILE=${CMAKE_SOURCE_DIR}/include/version.h
        -P ${CMAKE_SOURCE_DIR}/AutoVersion.cmake
)
ADD_DEPENDENCIES(${PROJECT_NAME} auto_increment_version)
# TODO: Add tests and install targets if needed.
