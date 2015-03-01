project(ONCommon)
set(PROJECT_VERSION ON_VERSION)
cmake_minimum_required(VERSION 3.0)

find_package(Qt5Core REQUIRED)
set(CMAKE_AUTOMOC ON)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
qt5_use_modules(${PROJECT_NAME} Core)
