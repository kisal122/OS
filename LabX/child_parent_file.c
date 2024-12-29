#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    FILE *file;
    pid_t pid;

    // Open the file for appending
    file = fopen("child_parent.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Fork to create a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        fclose(file);
        return 1;
    }

    if (pid == 0) { // Child process
        fprintf(file, "Child PID: %d\n", getpid());
    } else { // Parent process
        fprintf(file, "Parent PID: %d\n", getpid());
    }

    // Close the file
    fclose(file);

    return 0;
}
