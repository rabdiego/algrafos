ALL: main

main: algrafos03.o queue.o
	gcc algrafos03.o queue.o -o main

algrafos03.o: algrafos03.c queue.c queue.h
	gcc -c algrafos03.c

queue.o: queue.c queue.h
	gcc -c queue.c

clean:
	rm -f *.o main