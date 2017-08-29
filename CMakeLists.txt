cmake_minimum_required(VERSION 2.8.11)

project(qt-sudoku)

option(TESTS "Enable Tests" OFF)

#if(WIN32)
    set(CMAKE_PREFIX_PATH "C:\\Qt\\5.9.1\\msvc2015_64\\")
#endif()
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets)

set(CXX_FLAGS "")
if(CMAKE_COMPILER_IS_GNUCC OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
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

file(GLOB SOURCES "src/*.cpp")

include(CTest)
add_test(run qt-sudoku)
if(TESTS)
  include(ExternalProject)

  set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/googletest)
  ExternalProject_Add(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.8.0
    TIMEOUT 10
    # Force separate output paths for debug and release builds to allow easy
    # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
               -Dgtest_force_shared_crt=ON
               -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
               -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
    # Disable install step
    INSTALL_COMMAND ""
    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
  )

  file(GLOB SOURCES_TESTS "${PROJECT_SOURCE_DIR}/tests/*.cpp")
  list(APPEND SOURCES_TESTS ${SOURCES})
  list(REMOVE_ITEM SOURCES_TESTS "${PROJECT_SOURCE_DIR}/src/main.cpp")
  add_executable(qt-sudoku_tests "${SOURCES_TESTS}")
  add_dependencies(qt-sudoku_tests googletest)

  ExternalProject_Get_Property(googletest SOURCE_DIR)
  target_include_directories(qt-sudoku_tests SYSTEM PUBLIC "${SOURCE_DIR}/googletest/include" "src")

  if(MSVC)
    set(Suffix ".lib")
  else()
    set(Suffix ".a")
    set(Pthread "-pthread")
  endif()
  ExternalProject_Get_Property(googletest BINARY_DIR)
  if(UNIX)
	set(UNIX_LDD_FLAGS "-Wl,-O3")
  endif()
  target_link_libraries(qt-sudoku_tests ${UNIX_LDD_FLAGS}
    debug "${BINARY_DIR}/googlemock/gtest/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}"
    optimized "${BINARY_DIR}/googlemock/gtest/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}"
    ${Pthread}
  )
  target_link_libraries(qt-sudoku_tests ${UNIX_LDD_FLAGS}
    debug "${BINARY_DIR}/googlemock/gtest/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${Suffix}"
    optimized "${BINARY_DIR}/googlemock/gtest/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${Suffix}"
    ${Pthread}
  )
  target_link_libraries(qt-sudoku_tests Qt5::Widgets)

  add_test(Sudoku qt-sudoku_tests --gtest_filter=Sudoku.*)
endif()

add_executable(qt-sudoku ${SOURCES})
target_compile_options(qt-sudoku PUBLIC ${CXX_FLAGS})
if(TESTS)
    target_compile_options(qt-sudoku_tests PUBLIC ${CXX_FLAGS})
endif()

find_program(MEMORYCHECK_COMMAND valgrind)
set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes \
                                 --leak-check=full \
                                 --show-reachable=yes"
)

target_link_libraries(qt-sudoku Qt5::Widgets)