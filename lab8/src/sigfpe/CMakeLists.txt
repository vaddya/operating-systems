project(sigfpe)

add_executable(${PROJECT_NAME} sigfpe.cpp)

target_link_libraries(${PROJECT_NAME} utils)
target_include_directories(${PROJECT_NAME} PUBLIC ../utils)
