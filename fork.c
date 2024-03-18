#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork(); // Create a new process

    if (pid < 0) {
        // If fork() returns -1, an error occurred
        perror("fork failed");
        return -1;
    } else if (pid == 0) {
        // Child process
        printf("This is the child process. PID = %d, Parent PID = %d\n", getpid(), getppid());
    } else {
        // Parent process
        printf("This is the parent process. PID = %d, Child PID = %d\n", getpid(), pid);
        sleep(1); // Sleep is used here to prevent the parent from exiting before the child,
                  // which would make the child's parent PID become 1 (the init process).
    }

    return 0;
}
