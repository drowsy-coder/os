#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int status;

    pid = fork(); // Create a new process

    if (pid < 0) {
        // If fork() returns -1, an error occurred
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("This is the child process. PID = %d\n", getpid());
        // Child process does something
        sleep(2); // Simulate some operation by sleeping for 2 seconds
        printf("Child process is exiting.\n");
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        printf("This is the parent process. PID = %d\n", getpid());
        // Parent process waits for the child to complete
        wait(&status); // Wait for child process to terminate
        if (WIFEXITED(status)) {
            printf("Child process exited with status = %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process did not exit successfully\n");
        }
        printf("Parent process continues...\n");
    }

    printf("Both parent and child are done.\n");
    return EXIT_SUCCESS;
}
