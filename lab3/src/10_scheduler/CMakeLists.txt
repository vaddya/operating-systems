project(10_scheduler)

add_executable(father_scheduler father.c utils.c)
add_executable(son_scheduler son.c utils.c)
add_executable(father_priority father_priority.c utils.c)
add_executable(son_calc son_calc.c utils.c)
add_executable(interval interval.c utils.c)
add_executable(nesting nesting.c utils.c)
