cmake_minimum_required(VERSION 2.8.4)
project(poker)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ./include/card.hpp ./include/combination.hpp ./include/exceptions.hpp ./include/player.hpp ./src/player.cpp ./src/card.cpp ./src/combination.cpp)
add_executable(poker ${SOURCE_FILES})