cmake_minimum_required(VERSION 3.26)
project(aoc2023 C)

set(CMAKE_C_STANDARD 23)

add_library(d1 OBJECT day1/d1.c day1/d1.h)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} d1)