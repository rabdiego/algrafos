ALL: main

main: main.o queue.o linked_list.o
	g++ main.o queue.o linked_list.o -o main

main.o: main.cpp queue.cpp queue.h linked_list.cpp linked_list.h
	g++ -c main.cpp

linked_list.o: linked_list.cpp linked_list.h node.h
	g++ -c linked_list.cpp

queue.o: queue.cpp queue.h node.h
	g++ -c queue.cpp

clean:
	rm -f *.o main