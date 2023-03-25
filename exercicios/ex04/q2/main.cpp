#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "linked_list.h"

LinkedList *getDistance(int *graph, int n, int v) {
    LinkedList *lists = (LinkedList *) malloc(sizeof(LinkedList) * n);
    int *boolean = (int *) malloc(sizeof(int) * n);
    Queue searchQueue;

    for (int i = 0; i < n; i++) {
        if (i != v) {
            lists[i].head = NULL;
            boolean[i] = 0;
        }
    }
    
    boolean[v] = 1;

    searchQueue.initialize();
    searchQueue.enqueue(v);

    while (searchQueue.isEmpty() == 0) {
        int u = searchQueue.dequeue();
        for (int i = 0; i < n; i++) {
            if (*(graph + u*n + i) == 1 && boolean[i] == 0) {
                lists[i] = lists[u].copy();
                lists[i].push(i);
                searchQueue.enqueue(i);
                boolean[i] = 1;
            }   
        }
    }

    return lists;
}

int main() {
    int graph[7][7] = {
        {0, 1, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0}
    };

    LinkedList *l = getDistance(&graph[0][0], 7, 0);
    l[4].print();
}
