cmake_minimum_required(VERSION 3.10)
project(task_3)

set(CMAKE_CXX_STANDARD 11)

add_executable(task_3 task_3.cpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/temp.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
