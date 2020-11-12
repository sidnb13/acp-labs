cmake_minimum_required(VERSION 3.17)
project(lasalle)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        *.h
        *.cpp
        )

add_executable(lasalle main.cpp ${SOURCES})