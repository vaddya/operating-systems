project(sigexam)

add_executable(${PROJECT_NAME} sigexam.c)

add_subdirectory(sigsender)
add_subdirectory(sigthread)
