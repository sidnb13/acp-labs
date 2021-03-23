cmake_minimum_required(VERSION 3.17)
project(avl_tree)

set(CMAKE_CXX_STANDARD 17)

add_executable(avl_tree main.cpp AVLTree.cpp AVLTree.h)