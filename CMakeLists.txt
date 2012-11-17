project(ON)
cmake_minimum_required(VERSION 2.8)

set(ON_BINARY_DIR ${PROJECT_BINARY_DIR}/bin)

# Common output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ON_BINARY_DIR} CACHE PATH "Single Directory for all Executables.")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ON_BINARY_DIR} CACHE PATH "Single Directory for all Libraries")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ON_BINARY_DIR} CACHE PATH "Single Directory for all static libraries.")

# Enable C++11
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif()

add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(clients)

enable_testing()
add_test(ONCommon ${ON_BINARY_DIR}/ONCommon-Tests)
