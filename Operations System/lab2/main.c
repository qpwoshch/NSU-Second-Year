#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

ssize_t my_write(int fd, const void *buf, size_t count) {
    return syscall(SYS_write, fd, buf, count);
}

//void assembler(const char* msg) {
//    long len = 0;
//    while (msg[len] != '\0') {
//        len++;
//    }
//    asm(
//            "movq $1, %%rax;"
//            "movq $1, %%rdi;"
//            "movq %0, %%rsi;"
//            "movq %1, %%rdx;"
//            "syscall;"
//            :
//            : "r"(msg), "r"(len)
//            : "rax", "rdi", "rsi", "rdx"
//            );
//}

int main(void) {
    printf("Hello World\n");
//    const char message[] = "Hello, World!\n";
//    write(1, message, sizeof(message)-1);
//    my_write(1, message, sizeof(message) - 1);
//    assembler(message);
    return 0;
}