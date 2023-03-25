#ifndef queue_h
#define queue_h

#include "node.h"

class Queue {
    public:
        Node *head;
        void initialize();
        int isEmpty();
        void enqueue(int);
        int dequeue();
};

#endif