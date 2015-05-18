cmake_minimum_required(VERSION 3.1)
project(Cool_Things)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set(SOURCE_FILES main.cpp)
add_executable(Cool_Things ${SOURCE_FILES} safe_printf.h dumper.h namer.h concurrency.h units.h evector.h intvector.h)