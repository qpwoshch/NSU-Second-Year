#include <stdio.h>

void hello_from_dynamic_lib();

int main() {
    printf("Calling function from library\n");
    hello_from_dynamic_lib();
    return 0;
}