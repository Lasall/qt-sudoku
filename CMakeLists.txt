cmake_minimum_required(VERSION 2.8.11)

project(qt-sudoku)

#if(WIN32)
    set(CMAKE_PREFIX_PATH "C:\\Qt\\5.9.1\\msvc2015_64\\")
#endif()
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets)

file(GLOB SOURCES src/*.cpp src/*.h)

add_executable(qt-sudoku ${SOURCES})

target_link_libraries(qt-sudoku Qt5::Widgets)