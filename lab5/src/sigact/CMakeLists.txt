project(sigact)

add_executable(${PROJECT_NAME} sigact.c)

add_subdirectory(sighandler)
