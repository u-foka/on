project(ON)
set(PROJECT_VERSION DETECTED_ON_VERSION)
cmake_minimum_required(VERSION 3.0)

set(ON_SOURCE_ROOT_DIR ${PROJECT_SOURCE_DIR})

# Enable C++11
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_definitions(-std=gnu++0x)
endif()
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_definitions(-std=c++11)
endif()

# Defines
if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()

if(USE_READLINE)
    message(STATUS "Enabled readline support")
    find_package(Readline REQUIRE)
endif()

include(DateTime)
DATE(CURR_DATE)
YEAR(CURR_YEAR)

configure_file(config.h.in config.h)
add_definitions(-include "\"${CMAKE_CURRENT_BINARY_DIR}/config.h\"")

add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(clients)

