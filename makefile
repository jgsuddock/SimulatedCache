Main: P1bCache.o
	gcc -o Main P1bCache.o

P1bCache.o: P1bCache.c
	gcc -c P1bCache.c
