project(exception_signal)

add_executable(${PROJECT_NAME} exception_signal.cpp)

target_link_libraries(${PROJECT_NAME} exceptions utils)
target_include_directories(${PROJECT_NAME} PUBLIC ../exceptions ../utils)
