#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int global_var = 42;

int main() {
    int local_var = 24;

    printf("=== [Parent] ===\n");
    printf("PID: %d\n", getpid());
    printf("Address of global_var: %p, value: %d\n", (void*)&global_var, global_var);
    printf("Address of local_var: %p, value: %d\n", (void*)&local_var, local_var);
    sleep(7);
    pid_t pid = fork();



    if (pid == 0) {
        printf("\n=== [Child] ===\n");
        printf("PID: %d, Parent PID: %d\n", getpid(), getppid());

        printf("Address of global_var (child): %p, value: %d\n", (void*)&global_var, global_var);
        printf("Address of local_var (child): %p, value: %d\n", (void*)&local_var, local_var);

        global_var = 100;
        local_var = 200;

        printf("Modified global_var (child): %d\n", global_var);
        printf("Modified local_var (child): %d\n", local_var);

        exit(5);
    } else {
        sleep(15);

        printf("\n=== [Parent after sleep] ===\n");
        printf("global_var: %d\n", global_var);
        printf("local_var: %d\n", local_var);

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            printf("Child exited normally with code %d\n", code);
        } else if (WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);
            printf("Child terminated by signal %d\n", sig);
        } else {
            printf("Child terminated abnormally (no exit code)\n");
        }
    }

    return 0;
}
