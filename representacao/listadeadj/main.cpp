#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

int main() {
    DynamicArray a;
    a.initialize();
    a.append(5);
    a.append(3);
    printf("%d\n", *(a.head));
    return 0;
}
