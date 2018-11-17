all: father son son_calc nesting father_priority interval

father: father.c utils.c
	gcc -o father father.c utils.c

son: son.c utils.c
	gcc -o son son.c utils.c

son_calc: son_calc.c utils.c
	gcc -o son_calc son_calc.c utils.c

nesting: nesting.c utils.c
	gcc -o nesting nesting.c utils.c

father_priority: father_priority.c utils.c
	gcc -o father_priority father_priority.c utils.c

interval: interval.c utils.c
	gcc -o interval interval.c utils.c

clean:
	rm father son son_calc nesting father_priority interval
