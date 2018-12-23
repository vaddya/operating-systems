cmake_minimum_required(VERSION 3.10)
project(src)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(pipe)
add_subdirectory(named_pipe)
add_subdirectory(socket)
add_subdirectory(signal)
add_subdirectory(shmem)
add_subdirectory(mailslot)
