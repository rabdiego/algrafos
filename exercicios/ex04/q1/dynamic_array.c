#include <stdlib.h>
#include "dynamic_array.h"

void initialize(DynamicArray **a) {
    (*a)->head = (int *) malloc(sizeof(int));
    (*a)->max = 1;
    (*a)->n = 0;
}

int isEmpty(DynamicArray **a) {
    if ((*a)->n == 0)
        return 1;
    return 0;
}

void append(DynamicArray **a, int k) {
    *((*a)->head + (*a)->n) = k;
    (*a)->n++;
    if ((*a)->n == (*a)->max) {
        (*a)->max *= 2;
        int *temp = (int *) malloc(sizeof(int) * (*a)->max);
        int *toFree = (*a)->head;

        for (int i = 0; i < (*a)->n; i++) {
            temp[i] = toFree[i];
        }

        (*a)->head = temp;
        free(toFree);
    }
}

int pop(DynamicArray **a) {
    int *toFree = (*a)->head + (*a)->n - 1;
    int return_value = *(toFree);
    (*a)->n--;
    if ((*a)->n < ((*a)->max)/2) {
        (*a)->max /= 2;
        int *temp = (int *) malloc(sizeof(int) * (*a)->max);
        int *toFree = (*a)->head;

        for (int i = 0; i < (*a)->n; i++) {
            temp[i] = toFree[i];
        }

        (*a)->head = temp;
        free(toFree);
    }
    return return_value;
}