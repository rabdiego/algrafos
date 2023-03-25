#ifndef dynamic_array_h
#define dynamic_array_h

typedef struct {
    int *head;
    int max;
    int n;
} DynamicArray;

void initialize(DynamicArray **);
int isEmpty(DynamicArray **);
void append(DynamicArray **, int);
int pop(DynamicArray **);

#endif