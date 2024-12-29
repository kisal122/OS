#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int sig) {
    if (sig == SIGUSR1) {
        printf("Child: Received SIGUSR1 signal from parent!\n");
    }
}

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) { // Child process
        // Register signal handler
        signal(SIGUSR1, handle_signal);
        printf("Child: Waiting for signal from parent...\n");

        while (1) {
            pause(); // Suspend until a signal is received
        }
    } else { // Parent process
        // Parent process sleeps for 2 seconds
        sleep(2);

        printf("Parent: Sending SIGUSR1 signal to child (PID: %d)\n", pid);

        kill(pid, SIGUSR1);

        sleep(1);
    }

    return 0;
}
