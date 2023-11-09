cmake_minimum_required(VERSION 3.26)
project(ctdl_gk)

set(CMAKE_CXX_STANDARD 17)

add_executable(ctdl_gk main.cpp
        UserInterface.cpp
        UserInterface.h)
