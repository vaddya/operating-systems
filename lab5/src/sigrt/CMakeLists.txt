project(sigrt)

add_executable(${PROJECT_NAME} sigrt.c)

target_link_libraries(${PROJECT_NAME} pthread)
