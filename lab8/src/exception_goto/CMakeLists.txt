project(exception_goto)

add_executable(${PROJECT_NAME} exception_goto.cpp)

target_link_libraries(${PROJECT_NAME} exceptions)
target_include_directories(${PROJECT_NAME} PUBLIC ../exceptions)
