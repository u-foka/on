project(ONCommonProtocol)
cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)
set(QT_USE_CORE TRUE)
set(QT_USE_GUI FALSE)
set(QT_USE_QTNETWORK TRUE)
set(QT_USE_QTSQL TRUE)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

include_directories(${ON_SOURCE_ROOT_DIR}/common)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

qt4_wrap_cpp(HEADERS_MOC ${HEADERS})
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS} ${HEADERS_MOC})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})
