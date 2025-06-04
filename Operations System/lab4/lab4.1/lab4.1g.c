#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main() {
    char* var = getenv("MY_VAR");
    printf("Variable value before change: %s\n", var);
    char new_val[] = "New value";
    setenv("MY_VAR", new_val, 1);
    var = getenv("MY_VAR");
    printf("Variable value after change: %s\n", var);
    return 0;
}