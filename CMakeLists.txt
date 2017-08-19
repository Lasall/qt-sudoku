cmake_minimum_required(VERSION 2.8.11)

project(qt-sudoku)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)

#if(WIN32)
#    add_executable(qt-sudoku WIN32 main.cpp)
#else()
    add_executable(qt-sudoku main.cpp window.cpp)
#endif()

target_link_libraries(qt-sudoku Qt5::Widgets)