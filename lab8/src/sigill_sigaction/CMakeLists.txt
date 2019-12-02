project(sigill_sigaction)

add_executable(${PROJECT_NAME} sigill_sigaction.cpp)

target_link_libraries(${PROJECT_NAME} utils)
target_include_directories(${PROJECT_NAME} PUBLIC ../utils)
