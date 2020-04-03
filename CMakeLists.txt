# cmake_minimum_required(VERSION <specify CMake version here>)
project(15Puzzle)

set(CMAKE_LEGACY_CYGWIN_WIN32 0)

add_executable(15Puzzle main.cpp FifteenPuzzle.cpp)