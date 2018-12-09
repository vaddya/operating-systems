cmake_minimum_required(VERSION 3.10)
project(src)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(sigexam)
add_subdirectory(sigact)
add_subdirectory(sighandler)
add_subdirectory(pipe)
add_subdirectory(pipes)
add_subdirectory(queue)
add_subdirectory(semaphore)
add_subdirectory(semaphores)
add_subdirectory(tcp)

