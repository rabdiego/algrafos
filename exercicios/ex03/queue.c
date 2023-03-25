#include <stdlib.h>
#include "queue.h"

void initialize(Node **n) {
    (*n) = NULL;
}

int isNull(Node **n) {
    if ((*n) == NULL)
        return 1;
    return 0;
}

void enqueue(Node **n, int key) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;
    Node *a = NULL, *b = (*n);
    
    while (b != NULL) {
        a = b;
        b = b->next;
    }

    if (a != NULL) {
        a->next = newNode;
    } else {
        (*n) = newNode;
    }
}

int dequeue(Node **n) {
    int return_value = (*n)->key;
    Node *toFree = (*n);
    (*n) = toFree->next;
    free(toFree);
    return return_value;
}
