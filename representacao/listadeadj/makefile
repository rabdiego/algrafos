ALL: main

main: main.o  dynamic_array.o
	gcc main.o  -o main

main.o: main.c  dynamic_array.c dynamic_array.h
	gcc -c main.c


dynamic_array.o: dynamic_array.c dynamic_array.h
	gcc -c dynamic_array.c

clean:
	rm -f *.o main