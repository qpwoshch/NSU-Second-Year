#include <stdio.h>

void hello_from_static_lib();

int main(void) {
    printf("Calling function from our library\n");
    hello_from_static_lib();
    return 0;
}
