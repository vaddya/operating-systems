project(socket_multiecho_server)

add_executable(${PROJECT_NAME} server.cpp)

target_link_libraries(${PROJECT_NAME} socket_utils libws2_32.a)

target_include_directories(${PROJECT_NAME} PUBLIC ../../utils)
