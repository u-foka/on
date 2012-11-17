project(ON)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all Executables.")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all Libraries")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single Directory for all static libraries.")

add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(clients)
