#include "stdio.h"

int* func() {
    int variable = 10;
    return &variable;
}


int main() {
    int* ptr = func();
    printf("Address: %p\n", ptr);
    return 0;
}