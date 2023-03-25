#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *head;
    int max;
    int n;
} DynamicArray;

void initialize(DynamicArray **a) {
    (*a)->head = (int *) malloc(sizeof(int));
    (*a)->max = 1;
    (*a)->n = 0;
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

int main() {
    DynamicArray *a;
    initialize(&a);
    append(&a, 1);
    append(&a, 2);
    append(&a, 3);

    for (int i = 0; i < 3; i++) {
        printf("%d\n", *(a->head + i));
    }
    return 0;
}
