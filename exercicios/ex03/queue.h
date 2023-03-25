#ifndef queue_h
#define queue_h

typedef struct _node {
    int key;
    struct _node *next;
} Node;

void initialize(Node **);
int isNull(Node **);
void enqueue(Node **, int);
int dequeue(Node **);

#endif