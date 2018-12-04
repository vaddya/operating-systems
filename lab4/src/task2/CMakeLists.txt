cmake_minimum_required(VERSION 3.10)
project(task2)

set(CMAKE_CXX_STANDARD 11)

add_executable(task2 task2.cpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/temp.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})