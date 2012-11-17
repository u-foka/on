project(ONCommon)
cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

aux_source_directory(. SRC_LIST)
add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})
