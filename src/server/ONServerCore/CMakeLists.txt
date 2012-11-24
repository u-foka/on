project(ONServerCore)
cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)
set(QT_USE_CORE TRUE)
set(QT_USE_GUI FALSE)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

include_directories(${ON_SOURCE_ROOT_DIR}/common)
aux_source_directory(. SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ONCommon)
target_link_libraries(${PROJECT_NAME} ONCommonPosix)
