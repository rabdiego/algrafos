#ifndef dynamic_array_h
#define dynamic_array_h

class DynamicArray {
    public:
        int *head;
        int max;
        int n;
        void initialize();
        void append(int);
};

#endif