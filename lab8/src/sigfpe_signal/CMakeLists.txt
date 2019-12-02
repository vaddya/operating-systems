project(sigfpe_signal)

add_executable(${PROJECT_NAME} sigfpe_signal.cpp)

target_link_libraries(${PROJECT_NAME} utils)
target_include_directories(${PROJECT_NAME} PUBLIC ../utils)
