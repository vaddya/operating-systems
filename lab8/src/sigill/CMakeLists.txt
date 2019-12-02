project(sigill)

add_executable(${PROJECT_NAME} sigill.cpp)

target_link_libraries(${PROJECT_NAME} utils)
target_include_directories(${PROJECT_NAME} PUBLIC ../utils)
