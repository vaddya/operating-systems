project(socket_udp_server)

add_executable(${PROJECT_NAME} server.cpp)

target_link_libraries(${PROJECT_NAME} libws2_32.a)
