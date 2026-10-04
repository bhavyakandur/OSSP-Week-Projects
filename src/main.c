#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

int main()
{
    char input[1024];

    printf("=====================================\n");
    printf(" Welcome to ShellForge Version 1.0\n");
    printf("=====================================\n");

    while (1)
    {
        printf("myshell> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0)
        {
            printf("Exiting ShellForge...\n");
            break;
        }

        if (strncmp(input, "cd ", 3) == 0)
        {
            char *directory = input + 3;

            if (chdir(directory) != 0)
            {
                perror("cd failed");
            }

            continue;
        }

        if (strcmp(input, "cd") == 0)
        {
            printf("Usage: cd <directory>\n");
            continue;
        }

        execute_command(input);
    }

    return 0;
}
