project(ON)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_COLOR_MAKEFILE ON)

execute_process(COMMAND git describe
                OUTPUT_VARIABLE ON_VERSION)

set(PROJECT_VERSION ON_VERSION)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(ON_BINARY_DIR ${PROJECT_BINARY_DIR}/bin)

# Common output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ON_BINARY_DIR} CACHE PATH "Single Directory for all Executables.")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ON_BINARY_DIR} CACHE PATH "Single Directory for all Libraries")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ON_BINARY_DIR} CACHE PATH "Single Directory for all static libraries.")

# Source
add_subdirectory(src)

# Testing
enable_testing()
add_test(ONCommon ${ON_BINARY_DIR}/ONCommon-Tests)

# Documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc ALL
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile > /dev/null
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)
