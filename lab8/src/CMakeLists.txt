cmake_minimum_required(VERSION 3.15)
project(lab8)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(utils)
add_subdirectory(sigfpe)
add_subdirectory(sigill)
add_subdirectory(sigfpe_signal)
add_subdirectory(sigill_signal)
add_subdirectory(sigfpe_sigaction)
add_subdirectory(sigill_sigaction)

add_subdirectory(signal_nested)
add_subdirectory(sigaction_nested)

add_subdirectory(exceptions)
add_subdirectory(exception_try_catch)
add_subdirectory(exception_signal)
add_subdirectory(exception_unwind)
add_subdirectory(exception_nested)
add_subdirectory(exception_goto)

add_subdirectory(logsys)
add_subdirectory(ioport)
