project(21_threads_handler)

add_executable(threads_handler threads_handler.c)
target_link_libraries(threads_handler pthread)
