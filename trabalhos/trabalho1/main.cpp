#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class DynamicArray {
    public:
        int *head;
        int max;
        int n;

        void initialize() {
            this->head = (int *) malloc(sizeof(int));
            this->max = 1;
            this->n = 0;
        }

        void append(int k) {
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
};

class AdjacencyList {
    public:
        DynamicArray *head;
        
        void initialize(int n) {
            this->head = (DynamicArray *) malloc(sizeof(DynamicArray) * n);
            for (int i = 0; i < n; i++)
                (this->head[i]).initialize();
        }

        void addEdge(int a, int b) {
            (this->head[a - 1]).append(b);
            (this->head[b - 1]).append(a);
        }

        int * getNeighbours(int a) {
            return (this->head[a - 1]).head;
        }

        int getDegree(int a) {
            return (this->head[a - 1]).n;
        }
};

int main() {
}