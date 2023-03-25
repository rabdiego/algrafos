#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dynamic_array.h"

void getDistance(int *graph, int n, int v) {
    int distance = 0;
    int *boolean = (int *) malloc(sizeof(int) * n);
    DynamicArray *a = (DynamicArray *) malloc(sizeof(DynamicArray));
    DynamicArray *p = (DynamicArray *) malloc(sizeof(DynamicArray));

    for (int i = 0; i < n; i++) {
        boolean[i] = 0;
    }

    initialize(&a);
    initialize(&p);
    append(&a, v);
    boolean[v] = 1;

    while (isEmpty(&a) == 0) {
        int u = pop(&a);
        distance++;
        for (int i = 0; i < n; i++) {
            if (*(graph + u*n + i) == 1 && boolean[i] == 0) {
                append(&p, i);
                boolean[i] = 1;
                printf("%d %d\n", i, distance);
            }
        }

        while (isEmpty(&p) == 0) {
            int toAppend = pop(&p);
            append(&a, toAppend);
        }
    }
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
    getDistance(&graph[0][0], 7, 0);
}
