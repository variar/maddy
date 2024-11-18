#version 1.3.0
cmake_minimum_required(VERSION 3.14)
project(maddy)

add_executable(maddy main.cpp)
target_include_directories(maddy SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
