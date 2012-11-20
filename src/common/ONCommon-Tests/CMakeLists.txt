project(ONCommon-Tests)
cmake_minimum_required(VERSION 2.8)

find_package(Threads)

find_package(Qt4 REQUIRED)
set(QT_USE_CORE TRUE)
set(QT_USE_GUI FALSE)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ONCommon)
target_link_libraries(${PROJECT_NAME} gtest)
target_link_libraries(${PROJECT_NAME} gmock)
target_link_libraries(${PROJECT_NAME} gmock_main)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
