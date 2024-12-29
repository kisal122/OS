#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

// Signal handler for the child process
void handle_signal(int sig) {
   if (sig == SIGUSR1) {
        printf("Child: Received signal SIGUSR1 from parent!\n");
    }
}

int main() {
    int pipefd[2];  // Pipe file descriptors
    pid_t pid;

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // Fork to create a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) { 
        close(pipefd[1]); 

        // Register signal handler
        signal(SIGUSR1, handle_signal);

        char buffer[10];
        read(pipefd[0], buffer, sizeof(buffer));
        close(pipefd[0]);  

        if (strcmp(buffer, "SIGUSR1") == 0) {
            kill(getpid(), SIGUSR1); // Trigger the signal for the child itself
        }
    } else { // Parent process
        close(pipefd[0]);  // Close unused read end of the pipe

        printf("Parent: Sending SIGUSR1 signal to child (via pipe).\n");

        write(pipefd[1], "SIGUSR1", strlen("SIGUSR1") + 1); // Write signal info to pipe
        close(pipefd[1]);  // Close write end of the pipe
    }

    return 0;
}
