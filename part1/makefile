tp: main.o graph.o degreeList.o auxfunc.o
	gcc -std=c11 -Wall main.o graph.o degreeList.o auxfunc.o -o tp -lm

auxfunc.o: src/auxfunc.c inc/auxfunc.h
	gcc  -std=c11 -Wall  -c src/auxfunc.c -lm

graph.o: src/graph.c inc/graph.h
	gcc  -std=c11 -Wall  -c src/graph.c -lm

degreeList.o: src/degreeList.c inc/degreeList.h
	gcc  -std=c11 -Wall  -c src/degreeList.c -lm

main.o: src/main.c
	gcc  -std=c11 -Wall  -c src/main.c -lm

.PHONY: clean

clean:
	rm main.o auxfunc.o graph.o degreeList.o

debug: main.o graph.o degreeList.o auxfunc.o
	gcc -std=c11 -Wall -ggdb3 main.o graph.o degreeList.o auxfunc.o -o tp -lm
