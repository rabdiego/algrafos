#include <stdlib.h>
#include "dynamic_array.h"

void DynamicArray::initialize() {
    this->head = (int *) malloc(sizeof(int));
    this->max = 1;
    this->n = 0;
}

void DynamicArray::append(int k) {
    *(this->head + this->n) = k;
    this->n++;

    if (this->n == this->max) {
        this->max *= 2;
        int *temp = (int *) malloc(sizeof(int) * this->max);
        int *toFree = this->head;

        for (int i = 0; i < this->n; i++) {
            temp[i] = toFree[i];
        }

        this->head = temp;
        free(toFree);
    }
}
