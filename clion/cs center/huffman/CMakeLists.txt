cmake_minimum_required(VERSION 2.8.4)
project(huffman)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp huffman.cpp)
add_executable(huffman ${SOURCE_FILES})
