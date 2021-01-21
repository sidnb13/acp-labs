cmake_minimum_required(VERSION 3.17)
project(la_queue_sidnb13)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(la_queue_sidnb13
        client.cpp
        client.h
        LaQueue.cpp
        lqueue.cpp
        lqueue.h
        PQueue.cpp
        PQueue.h
        server.cpp
        server.h
        siginfo.h)
