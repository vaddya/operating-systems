project(20_threads_signal)

add_executable(threads_signal threads_signal.c)
target_link_libraries(threads_signal pthread)
