#include <stdlib.h>
#include "adj_list.h"
#include "dynamic_array.cpp"

void AdjacencyList::initialize(int n) {
    this->head = (DynamicArray *) malloc(sizeof(DynamicArray) * n);
    for (int i = 0; i < n; i++)
        (this->head[i]).initialize();
}

void AdjacencyList::addEdge(int a, int b) {
    (this->head[a - 1]).append(b);
    (this->head[b - 1]).append(a);
}

int * AdjacencyList::getNeighbours(int a) {
    return (this->head[a - 1]).head;
}

int AdjacencyList::getDegree(int a) {
    return (this->head[a - 1]).n;
}
