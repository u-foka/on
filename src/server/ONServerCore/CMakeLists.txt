project(ONServerCore)
cmake_minimum_required(VERSION 2.8)

find_package(Readline)

find_package(Qt4 REQUIRED)
set(QT_USE_CORE TRUE)
set(QT_USE_GUI FALSE)
set(QT_USE_QTNETWORK TRUE)

configure_file(config.h.in config.h)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${ON_SOURCE_ROOT_DIR}/common)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

qt4_wrap_cpp(HEADERS_MOC ${HEADERS})
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${HEADERS_MOC})
target_link_libraries(${PROJECT_NAME} ONCommon)
target_link_libraries(${PROJECT_NAME} ONCommonPosix)
target_link_libraries(${PROJECT_NAME} ONCommonProtocol)
if (HAVE_READLINE)
    target_link_libraries(${PROJECT_NAME} ${READLINE_LIBRARY})
endif (HAVE_READLINE)
