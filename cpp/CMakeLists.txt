cmake_minimum_required(VERSION 3.26)
project(aoc2023cpp CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} main.cpp)

add_library(d1 OBJECT D1.cpp D1.h)

target_link_libraries(${PROJECT_NAME} d1)