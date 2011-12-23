cmake_minimum_required(VERSION 2.6)
project(riivtodolph)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")
find_package(Xerces)

add_library(riivxmlparse riivxmlparse.cpp)
add_executable(riivtodolph riivtodolph.cpp)

target_link_libraries(riivtodolph riivxmlparse xerces-c)
