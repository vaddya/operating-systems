project(tcp_server)

add_executable(${PROJECT_NAME} server.c)

target_link_libraries(${PROJECT_NAME} pthread)
