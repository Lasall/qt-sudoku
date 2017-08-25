cmake_minimum_required(VERSION 2.8.11)

project(qt-sudoku)

#if(WIN32)
    set(CMAKE_PREFIX_PATH "C:\\Qt\\5.9.1\\msvc2015_64\\")
#endif()
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets)

set(CXX_FLAGS "")
if(CMAKE_COMPILER_IS_GNUCC OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    list(APPEND CXX_FLAGS
      -O3 -ffast-math -pedantic -Wall -Wextra -Wcast-align
      -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2
      -Winit-self -Wmissing-declarations -Wmissing-include-dirs
      -Wold-style-cast -Woverloaded-virtual -Wredundant-decls
      -Wsign-conversion -Wsign-promo -Wswitch-default
      -Wundef -Weffc++
      -std=c++1z
    )
    if(CMAKE_COMPILER_IS_GNUCC)
        list(APPEND CXX_FLAGS
          -Wlogical-op
          -Wnoexcept
          -Wstrict-null-sentinel
          -fdiagnostics-color=always
          -Wswitch-bool
          -Wlogical-not-parentheses
          -Wsizeof-array-argument
          -Wbool-compare
          -Wshift-negative-value
          -Wshift-overflow=2
          -Wnull-dereference
          -Wduplicated-cond
        )
    endif()
endif()

file(GLOB SOURCES src/*.cpp src/*.h)

add_executable(qt-sudoku ${SOURCES})
target_compile_options(qt-sudoku PUBLIC ${CXX_FLAGS})

target_link_libraries(qt-sudoku Qt5::Widgets)