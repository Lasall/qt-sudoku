cmake_minimum_required(VERSION 2.8.11)

project(qt-sudoku)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)

file(GLOB SOURCES src/*.cpp)

#if(WIN32)
#    add_executable(qt-sudoku WIN32 main.cpp)
#else()
    add_executable(qt-sudoku ${SOURCES})
#endif()

target_link_libraries(qt-sudoku Qt5::Widgets)