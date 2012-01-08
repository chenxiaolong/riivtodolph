project(riivtodolph)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

add_executable(riivtodolph main.cpp)
target_link_libraries(riivtodolph ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
