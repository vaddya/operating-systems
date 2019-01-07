project(19_threads_kill)

add_executable(threads_kill threads_kill.c)
target_link_libraries(threads_kill pthread)
