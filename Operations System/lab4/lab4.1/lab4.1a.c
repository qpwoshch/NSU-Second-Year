#include "stdio.h"
#include <unistd.h>

int init = 10;
int uninit;
const int constGlobal = 5;

void func() {
    int localInFunc = 15;
    static int staticInFunc = 20;
    const int constInFunc = 25;
    printf("Address local in func variable: %p\n", &localInFunc);
    printf("Address static in func variable: %p\n", &staticInFunc);
    printf("Address const in func variable: %p\n", &constInFunc);
}

int main() {
    func();
    printf("Address global init variable: %p\n", &init);
    printf("Address global uninit variable: %p\n", &uninit);
    printf("Address global const variable: %p\n", &constGlobal);
    printf("PID: %d\n", getpid());
    sleep(30);
    return 0;
}