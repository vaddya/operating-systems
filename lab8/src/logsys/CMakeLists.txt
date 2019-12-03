project(logsys)

add_executable(${PROJECT_NAME} logsys.cpp)

target_link_libraries(${PROJECT_NAME} utils)
target_include_directories(${PROJECT_NAME} PUBLIC ../utils)
