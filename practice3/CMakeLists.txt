cmake_minimum_required(VERSION 3.17)
project(practice3)

set(CMAKE_CXX_STANDARD 14)

add_executable(practice3 main.cpp)

SET(CMAKE_CXX_FLAGS -pthread)