cmake_minimum_required(VERSION 3.17)
project(bin_tree)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(bin_tree
        BSTree.cpp
        BSTree.h
        main.cpp
        printPretty.cpp
        printPretty.h)
