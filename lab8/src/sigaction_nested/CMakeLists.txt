project(sigaction_nested)

add_executable(${PROJECT_NAME} sigaction_nested.cpp)

target_link_libraries(${PROJECT_NAME} utils)
target_include_directories(${PROJECT_NAME} PUBLIC ../utils)
