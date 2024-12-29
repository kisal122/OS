#include <stdio.h>
#include <unistd.h> 
#include <stdio.h>
int main() {
   

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            return 1; // Exit if fork fails
        }

        if (pid == 0) { // Child process
            printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
            break; // Stop further forking by the child process
        } else { // Parent process
            // Parent continues to the next iteration
        }
    }

    return 0;
}
