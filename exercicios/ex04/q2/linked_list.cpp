#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

void LinkedList::initialize() {
    this->head = NULL;
}

void LinkedList::push(int key) {
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

void LinkedList::print() {
    Node *a = NULL, *b = this->head;

    while (b != NULL) {
        printf("%d ", b->key);
        a = b;
        b = b->next;
    } printf("\n");
}

LinkedList LinkedList::copy() {
    LinkedList copy;
    copy.initialize();
    Node *b = this->head;

    while (b != NULL) {
        copy.push(b->key);
        b = b->next;
    }

    return copy;
}