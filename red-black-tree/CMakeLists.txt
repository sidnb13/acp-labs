cmake_minimum_required(VERSION 3.17)
project(red_black_tree)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(red_black_tree
        main.cpp
        RBtree.cpp
        RBtree.h)
