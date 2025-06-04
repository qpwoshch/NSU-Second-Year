#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        pid_t child = fork();

        if (child == 0) {
            printf("[C] Child of B. PID: %d, PPID: %d\n", getpid(), getppid());
            sleep(5);
            printf("[C] Exiting.\n");
            exit(0);
        } else {
            printf("[B] Parent of C. PID: %d, PPID: %d\n", getpid(), getppid());
            printf("[B] Exiting (will become zombie if A doesn't wait).\n");
            exit(0);
        }
    } else {
        printf("[A] Grandparent. PID: %d, waiting 20 seconds...\n", getpid());
        sleep(20);
        printf("[A] Exiting.\n");
    }

    return 0;
}
