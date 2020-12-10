cmake_minimum_required(VERSION 3.17)
project(lasalloc)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        *.h
        *.cpp
        )

add_executable(lasalloc main.cpp ${SOURCES})