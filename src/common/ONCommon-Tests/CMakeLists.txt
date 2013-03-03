project(ONCommon-Tests)
set(PROJECT_VERSION ON_VERSION)
cmake_minimum_required(VERSION 2.8)

find_package(Threads)

find_package(Qt4 REQUIRED)
set(QT_USE_CORE TRUE)
set(QT_USE_GUI FALSE)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

include_directories(${ON_SOURCE_ROOT_DIR}/common)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

qt4_wrap_cpp(HEADERS_MOC ${HEADERS})
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${HEADERS_MOC})
target_link_libraries(${PROJECT_NAME} ONCommon)
target_link_libraries(${PROJECT_NAME} ONCommonProtocol)
target_link_libraries(${PROJECT_NAME} gtest)
target_link_libraries(${PROJECT_NAME} gmock)
target_link_libraries(${PROJECT_NAME} gmock_main)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
