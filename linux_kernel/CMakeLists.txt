cmake_minimum_required(VERSION 3.16)
project(linux_kernel C)

set(CMAKE_C_STANDARD 11)

FILE(GLOB_RECURSE SOURCE *.c)

add_executable(linux_kernel ${SOURCE})

include_directories(/usr/src/linux-headers-${CMAKE_HOST_SYSTEM_VERSION}/include/)
