#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_CHILDREN 10

void execute_command() {

    printf("Files in directory:\n");
    char *args[] = {"ls", NULL};
    execvp(args[0], args);

    // If execvp fails
    perror("execvp failed");
    exit(1);
}

int main() {
    pid_t pids[NUM_CHILDREN];

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pids[i] = fork();
        int status;

        if (pids[i] < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pids[i] == 0) {
            printf("Child %d (PID: %d) executing...\n", i, getpid());
            execute_command();
        }
    
        pid_t child_pid = wait(&status);

        if (WIFEXITED(status)) {
            printf("Child with PID %d exited normally with status %d\n", child_pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child with PID %d terminated by signal %d\n", child_pid, WTERMSIG(status));
        }
    }

    // Parent process waits for all children
    for (int i = 0; i < NUM_CHILDREN; i++) {
        
    }

    printf("All child processes completed.\n");
    return 0;
}
