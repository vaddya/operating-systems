project(exception_unwind)

add_executable(${PROJECT_NAME} exception_unwind.cpp)

target_link_libraries(${PROJECT_NAME} exceptions)
target_include_directories(${PROJECT_NAME} PUBLIC ../exceptions)
