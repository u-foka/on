project(ONServerCore)
set(PROJECT_VERSION ON_VERSION)
cmake_minimum_required(VERSION 2.8)

find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
set(CMAKE_AUTOMOC ON)

include_directories(${ON_SOURCE_ROOT_DIR}/common)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
qt5_use_modules(${PROJECT_NAME} Core Network)
target_link_libraries(${PROJECT_NAME} ONCommon)
target_link_libraries(${PROJECT_NAME} ONCommonPosix)
target_link_libraries(${PROJECT_NAME} ONCommonProtocol)
