ALL: main

main: main.o  adj_list.o
	gcc main.o  -o main

main.o: main.cpp  adj_list.cpp adj_list.h
	g++ -c main.cpp

adj_list.o: adj_list.cpp adj_list.h dynamic_array.cpp dynamic_array.h
	g++ -c adj_list.cpp

dynamic_array.o: dynamic_array.cpp dynamic_array.h
	g++ -c dynamic_array.cpp

clean:
	rm -f *.o main