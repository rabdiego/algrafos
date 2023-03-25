#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "queue.h"

double *getDistance(int *graph, int n, int v) {
    double *distance = (double *) malloc(sizeof(double) * n);
    Node *searchQueue;

    for (int i = 0; i < n; i++) {
        if (i != v) {
            *(distance + i) = INFINITY;
        }
    }
    
    *(distance + v) = 0;

    initialize(&searchQueue);
    enqueue(&searchQueue, v);

    while (isNull(&searchQueue) == 0) {
        int u = dequeue(&searchQueue);
        for (int i = 0; i < n; i++) {
            if (*(graph + u*n + i) == 1) {
                if (*(distance + i) == INFINITY) {
                    *(distance + i) = *(distance + u) + 1;
                    enqueue(&searchQueue, i);
                }
            }   
        }
    }
    
    free(searchQueue);

    return distance;
}

int main() {
    double *vec = (double *) malloc(sizeof(double) * 5);
    int graph[7][7] = {
        {0, 1, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0}
    };

    vec = getDistance(&graph[0][0], 7, 0);
    for (int i = 0; i < 7; i++)
        printf("%f\n", *(vec + i));
    
}
