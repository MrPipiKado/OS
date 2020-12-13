cmake_minimum_required(VERSION 3.17)
project(Lab8)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab8 main.cpp)

SET(CMAKE_CXX_FLAGS -pthread)