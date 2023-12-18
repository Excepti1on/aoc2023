cmake_minimum_required(VERSION 3.22)

project(aoc2023 C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libs)

set(CMAKE_C_FLAGS "-g -mavx2 -fopenmp")

add_library(hashmap STATIC hashmap/map.c hashmap/map.h)

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

add_library(day12 OBJECT day12/d12.c day12/d12.h)

target_link_libraries(day12 hashmap)

add_library(day13 OBJECT day13/d13.c day13/d13.h)

add_library(day14 OBJECT day14/d14.c day14/d14.h)

add_library(day15 OBJECT day15/d15.c day15/d15.h)

add_library(day16 OBJECT day16/d16.c day16/d16.h)

add_library(day18 OBJECT day18/d18.c day18/d18.h)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} hashmap day1 day2 day3 day4 day5 day6 day7 day8 day9 day10 day11 day12 day13 day14 day15 day16 day18)