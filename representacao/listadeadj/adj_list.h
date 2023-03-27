#ifndef adj_list_h
#define adj_list_h

#include "dynamic_array.h"

class AdjacencyList {
    public:
        DynamicArray *head;
        
        void addEdge(int, int);
        int getSize();
        int * getNeighbours(int);
        int getDegree(int);
};

#endif