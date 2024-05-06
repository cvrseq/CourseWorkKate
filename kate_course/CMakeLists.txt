cmake_minimum_required(VERSION 3.28)
project(kate_course)

set(CMAKE_CXX_STANDARD 26)

add_executable(kate_course main.cpp
        description.cpp
        description.h)
