project(utils)

set(UTILS_SRC utils.h utils.cpp)

add_library(${PROJECT_NAME} STATIC ${UTILS_SRC})
