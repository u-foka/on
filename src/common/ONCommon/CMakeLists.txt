project(ONCommon)
cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)
set(QT_USE_CORE TRUE)
set(QT_USE_GUI FALSE)
set(QT_USE_QTNETWORK TRUE)
set(QT_USE_QTSQL TRUE)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

aux_source_directory(. SRC_LIST)
list(APPEND SRC_LIST protocol.h)
list(APPEND SRC_LIST iprotocol.h)

add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})
