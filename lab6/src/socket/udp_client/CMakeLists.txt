project(socket_udp_client)

add_executable(${PROJECT_NAME} client.cpp)

target_link_libraries(${PROJECT_NAME} libws2_32.a)
