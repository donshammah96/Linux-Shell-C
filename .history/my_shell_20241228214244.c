// Simple implementation of a Linux shell in C
// using the execvp system call to handle command execution.
// This shell will take user input, parse it into commands
// and arguments, and execute it using the execvp function.


// FEATURES OF THE SHELL:
// 1. The shell will display a prompt "my_shell> " to the user.
// 2. The shell will read user input from the standard input (stdin).
// 3. The shell will parse the input into an array of arguments.
// 4. The shell will fork a child process to execute the command.
// 5. The child process will execute the command using the execvp system call.
// 6. The parent process will wait for the child process to finish.
// 7. The shell will exit when the user enters the "exit" command.

// To compile the program, run the following command:
// gcc -o my_shell my_shell.c

// To run the program, run the following command:
// ./my_shell

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100

// Function to parse the input into an array of arguments
void parse_input(char *input, char **args) {
    int i = 0;
    args[i] = strtok(input, " \n");
    while (args[i] != NULL) {
        i++;
        args[i] = strtok(NULL, " \n");
    }
}

int main() {
    char input[MAX_INPUT];
    char *args[MAX_ARGS];

    while (1) {
        // Print shell prompt
        printf("my_shell> ");
        fflush(stdout);

        // Read user input
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            perror("Error reading input");
            continue;
        }

        // Exit the shell on "exit" command
        if (strncomp(input, "exit", 4) == 0) {
            break;
        }

        // Parse the input
        parse_input(input, args);

        if (args[0] == NULL) {
            continue; // No command entered
        }

        // Fork a child process to execute the command
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            continue;
        }

        if (pid == 0) {
            // Child process : Execute the command
            if (execvp(args[0], args) == -1) {
                perror("Execution failed");
            }
            exit(EXIT_FAILURE);
        } else {
            // Parent process : Wait for the cild to finish
            wait(NULL); 
        }
    }

    printf("Exiting shell. Goodbye!\n");
    return 0;
}