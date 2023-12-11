cmake_minimum_required(VERSION 3.22)

project(aoc2023 C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libs)

set(CMAKE_C_FLAGS "-g -mavx2 -fopenmp")

add_library(day1 OBJECT day1/d1.c day1/d1.h)

add_library(day2 OBJECT day2/d2.c day2/d2.h)

add_library(day3 OBJECT day3/d3.c day3/d3.h)

add_library(day4 OBJECT day4/d4.c day4/d4.h)

add_library(day5 OBJECT day5/d5.c day5/d5.h)

add_library(day6 OBJECT day6/d6.c day6/d6.h)

add_library(day7 OBJECT day7/d7.c day7/d7.h)

add_library(day8 OBJECT day8/d8.c day8/d8.h)

add_library(day9 OBJECT day9/d9.c day9/d9.h)

add_library(day10 OBJECT day10/d10.c day10/d10.h)

add_library(day11 OBJECT day11/d11.c day11/d11.h)


add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} day1 day2 day3 day4 day5 day6 day7 day8 day9 day10 day11)