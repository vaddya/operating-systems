project(23_signals)

add_executable(rtsignals rtsignals.c)
target_link_libraries(rtsignals pthread)
