project(sigthread)

add_executable(${PROJECT_NAME} sigthread.c)

target_link_libraries(${PROJECT_NAME} pthread)
