all: father_wait sons

father_wait: father_wait.c
	gcc -o father_wait father_wait.c

sons: son1.c son2.c son3.c
	gcc -o son1 son1.c
	gcc -o son2 son2.c
	gcc -o son3 son3.c

clean:
	rm father_wait son1 son2 son3
