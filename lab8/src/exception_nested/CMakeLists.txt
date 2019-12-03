project(exception_nested)

add_executable(${PROJECT_NAME} exception_nested.cpp)

target_link_libraries(${PROJECT_NAME} exceptions)
target_include_directories(${PROJECT_NAME} PUBLIC ../exceptions)
