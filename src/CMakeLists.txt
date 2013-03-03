project(ON)
set(PROJECT_VERSION ON_VERSION)
cmake_minimum_required(VERSION 2.8)

set(ON_SOURCE_ROOT_DIR ${PROJECT_SOURCE_DIR})

# Enable C++11
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif()

# Defines
if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()
add_definitions(-DON_SRC_ROOT="${PROJECT_SOURCE_DIR}")

find_package(Readline)

include(DateTime)
DATE(CURR_DATE)
YEAR(CURR_YEAR)

configure_file(config.h.in config.h)
add_definitions(-include "${CMAKE_CURRENT_BINARY_DIR}/config.h")

add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(clients)

