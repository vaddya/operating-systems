project(exceptions)

set(EXCEPTIONS_SRC exceptions.h exceptions.cpp)

add_library(${PROJECT_NAME} STATIC ${EXCEPTIONS_SRC})
