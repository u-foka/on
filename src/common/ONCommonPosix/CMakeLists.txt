project(ONCommonPosix)
set(PROJECT_VERSION DETECTED_ON_VERSION)
cmake_minimum_required(VERSION 3.0)

find_package(Qt5Core REQUIRED)
set(CMAKE_AUTOMOC ON)

include_directories(${ON_SOURCE_ROOT_DIR}/common)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
qt5_use_modules(${PROJECT_NAME} Core)
if(HAVE_READLINE)
    target_link_libraries(${PROJECT_NAME} ${READLINE_LIBRARY})
endif()
