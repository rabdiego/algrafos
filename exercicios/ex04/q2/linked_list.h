#ifndef linked_list_h
#define linked_list_h

#include "node.h"

class LinkedList {
    public:
        Node *head;
        void initialize();
        void push(int);
        void print();
        LinkedList copy();
};

#endif