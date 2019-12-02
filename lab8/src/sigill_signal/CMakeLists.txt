project(sigill_signal)

add_executable(${PROJECT_NAME} sigill_signal.cpp)

target_link_libraries(${PROJECT_NAME} utils)
target_include_directories(${PROJECT_NAME} PUBLIC ../utils)
