#include <stdlib.h>
#include "dynamic_array.h"

void DynamicArray::initialize() {
    this->head = (int *) malloc(sizeof(int));
    this->max = 1;
    this->n = 0;
}

void DynamicArray::append(int k) {
    // !- Bug [Double free or corruption]
    int indexToSwap = -1, i =0;
    
    while (i < this->n || indexToSwap != -1) {
        if (*(this->head + i) > k)
            indexToSwap = i-1;
        i++;
    }

    for (i = indexToSwap; i < this->n; i++) 
        *(this->head + i + 1) = *(this->head + i);

    *(this->head + indexToSwap) = k;
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
