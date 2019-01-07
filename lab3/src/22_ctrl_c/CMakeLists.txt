project(22_ctrl_c)

add_executable(ctrl_c ctrl_c.c)
target_link_libraries(ctrl_c pthread)

add_executable(process_ctrl_c process_ctrl_c.c)
target_link_libraries(process_ctrl_c pthread)

add_executable(threads_ctrl_c threads_ctrl_c.c)
target_link_libraries(threads_ctrl_c pthread)

add_executable(process_ctrl_z process_ctrl_z.c)
target_link_libraries(process_ctrl_z pthread)
