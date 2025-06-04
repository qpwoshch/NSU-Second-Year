#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void func() {
    char* ptr = malloc(100*sizeof(char));
    strcpy(ptr, "Hello world!");
    printf("data in first buf before free: %s\n", ptr);
    free(ptr);
    printf("data in first buf after free: %s\n", ptr);
    char* ptr1 = malloc(100*sizeof(char));
    strcpy(ptr1, "Hello world!");
    printf("data in second buf before shift of the ptr: %s\n", ptr1);
    char* mid = ptr1+sizeof(ptr1)/2;
    free(mid);
    printf("data in second buf after shift of the ptr: %s\n", ptr1);
    free(ptr1);
}


int main() {
    func();
    return 0;
}

