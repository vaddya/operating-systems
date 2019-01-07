project(18_threads)

add_executable(threads threads.c)
target_link_libraries(threads pthread)
