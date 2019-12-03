project(exception_try_catch)

add_executable(${PROJECT_NAME} exception_try_catch.cpp)

target_link_libraries(${PROJECT_NAME} exceptions)
target_include_directories(${PROJECT_NAME} PUBLIC ../exceptions)
