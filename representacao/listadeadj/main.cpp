#include <stdio.h>
#include <stdlib.h>
#include "adj_list.cpp"

int main() {
    AdjacencyList a;
    a.initialize(10);
    a.addEdge(1, 2);
    a.addEdge(2, 3);
    printf("%d\n", a.getDegree(2));
    return 0;
}
