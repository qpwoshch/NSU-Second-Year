#include <stdio.h>
#include <unistd.h>

int main() {
    printf("PID: %d\n", getpid());
    sleep(10);
    char *args[] = {"./lab4.2a", NULL};
    execvp(args[0], args);
    execlp(args[0], "ls", "-l", 0);

    printf("Hello world\n");
    return 0;
}