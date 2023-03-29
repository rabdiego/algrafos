#ifndef adj_list_h
#define adj_list_h

#include "dynamic_array.h"

class AdjacencyList {
    public:
        DynamicArray *head;
        
        void initialize(int);
        void addEdge(int, int);
        int * getNeighbours(int);
        int getDegree(int);
};

#endif