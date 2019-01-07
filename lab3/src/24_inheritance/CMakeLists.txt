project(24_inheritance)

add_executable(inheritance inheritance.c utils.c)
target_link_libraries(inheritance pthread)
