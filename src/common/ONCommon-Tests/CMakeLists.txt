project(ONCommon-Tests)
set(PROJECT_VERSION DETECTED_ON_VERSION)
cmake_minimum_required(VERSION 3.0)

find_package(Threads)

find_package(Qt5Core REQUIRED)
set(CMAKE_AUTOMOC ON)

include_directories(${ON_SOURCE_ROOT_DIR}/common)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
qt5_use_modules(${PROJECT_NAME} Core)
target_link_libraries(${PROJECT_NAME} ONCommon)
target_link_libraries(${PROJECT_NAME} ONCommonProtocol)
target_link_libraries(${PROJECT_NAME} gtest)
target_link_libraries(${PROJECT_NAME} gmock)
target_link_libraries(${PROJECT_NAME} gmock_main)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
