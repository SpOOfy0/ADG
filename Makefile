all: test2 graph.o 

graph.o: graph.c graph.h
	gcc -c graph.c

outils.o: outils.c outils.h
	gcc -c outils.c

test2: test2.c graph.c outils.c graph.h outils.h
	gcc -Wall -o test2 test2.c graph.c outils.c

debug: test2.c graph.c outils.c graph.h outils.h
	gcc -g -Wall -o test2 test2.c graph.c outils.c
	gdb test2

clean:
	rm -f *.o test2
