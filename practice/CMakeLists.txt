cmake_minimum_required(VERSION 3.17)
project(Lab3)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp)

set(CMAKE_EXE_LINKER_FLAGS "-static")