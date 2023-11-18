cmake_minimum_required(VERSION 3.26)
project(ctdl_gk)

set(CMAKE_CXX_STANDARD 17)

add_executable(ctdl_gk main.cpp
        UserInterface.h
        UserInterface.cpp
        UserData.cpp
        UserData.h
        LinkedList.cpp
        CsvFile.cpp
        CsvFile.h
        UserAction.cpp
        UserAction.h
        Users.cpp
        Users.h
)
