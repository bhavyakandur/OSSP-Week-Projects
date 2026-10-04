#include <stdio.h>
#include <string.h>
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

        execute_command(input);
    }

    return 0;
}
