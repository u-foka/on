project(ON)
cmake_minimum_required(VERSION 2.8)

# Enable C++11
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif()

add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(clients)

