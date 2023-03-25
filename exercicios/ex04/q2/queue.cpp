#include <stdlib.h>
#include "queue.h"

void Queue::initialize() {
    this->head = NULL;
}

int Queue::isEmpty() {
    if (this->head == NULL)
        return 1;
    return 0;
}

void Queue::enqueue(int key) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;
    Node *a = NULL, *b = this->head;
    
    while (b != NULL) {
        a = b;
        b = b->next;
    }

    if (a != NULL) {
        a->next = newNode;
    } else {
        this->head = newNode;
    }
}

int Queue::dequeue() {
    Node *toFree = this->head;
    if (toFree == NULL)
        return -1;
    int return_value = toFree->key;
    this->head = toFree->next;
    free(toFree);
    return return_value;
}
