project(socket_tcp_client)

add_executable(${PROJECT_NAME} client.cpp)

target_link_libraries(${PROJECT_NAME} socket_utils libws2_32.a)

target_include_directories(${PROJECT_NAME} PUBLIC ../utils)
