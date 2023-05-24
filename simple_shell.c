#include "simple_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100

int main(int argc, char **argv)
{
    while (1)
    {
        write(STDOUT_FILENO, "$ ", 2);

        // Read the command from the user
        char command[MAX_COMMAND_LENGTH];
        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            // End of file condition (Ctrl+D)
            write(STDOUT_FILENO, "\n", 1);
            break;
        }

        // Remove trailing newline character
        command[strcspn(command, "\n")] = '\0';

        // Fork and execute the command
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Child process
            execlp(command, command, NULL);

            // If execlp returns, an error occurred
            perror("Command execution error");
            exit(EXIT_FAILURE);
        }
        else
        {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return (0);
}
