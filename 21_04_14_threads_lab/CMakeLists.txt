cmake_minimum_required(VERSION 3.16)
project(21_04_14_threads_lab)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(21_04_14_threads_lab main.cpp)