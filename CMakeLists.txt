cmake_minimum_required(VERSION 3.28)
project(BMPReader)

set(CMAKE_CXX_STANDARD 17)

add_executable(BMPReader main.cpp
        BMPReader.h
        BMPReader.cpp)
