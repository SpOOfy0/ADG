all: test2 graph.o 

graph.o: graph.c graph.h
	gcc -c graph.c

test2: test2.c graph.c graph.h 
	gcc -Wall -o test2 test2.c graph.c

debug: test2.c graph.c graph.h
	gcc -g -Wall -o test2 test2.c graph.c
	gdb test2

clean:
	rm -f *.o test2
