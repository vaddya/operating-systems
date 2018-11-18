all: fathers sons

fathers: father.c
	gcc -o father father.c
	gcc -o father_active_passive father_active_passive.c

sons: son1.c son2.c son3.c
	gcc -o son1 son1.c
	gcc -o son2 son2.c
	gcc -o son3 son3.c
	gcc -o son_active son_active.c
	gcc -o son_passive son_passive.c

clean:
	rm father father_active_passive son1 son2 son3 son_active son_passive
