project(ONCommon-Tests)
set(PROJECT_VERSION DETECTED_ON_VERSION)
cmake_minimum_required(VERSION 3.0)

find_package(GMock)

if(GMOCK_FOUND)

    find_package(Threads REQUIRED)
    find_package(Qt5Core REQUIRED)
    set(CMAKE_AUTOMOC ON)

    include_directories(${ON_SOURCE_ROOT_DIR}/common)
    include_directories(GMOCK_INCLUDE_DIRS)

    file(GLOB SOURCES *.cpp)
    file(GLOB HEADERS *.h)

    add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
    qt5_use_modules(${PROJECT_NAME} Core)
    target_link_libraries(${PROJECT_NAME} ONCommon)
    target_link_libraries(${PROJECT_NAME} ONCommonProtocol)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
    target_link_libraries(${PROJECT_NAME} GMOCK_MAIN_LIBRARIES)

    enable_testing()
    add_test(ONCommon ${ON_BINARY_DIR}/ONCommon-Tests)

endif(GMOCK_FOUND)
