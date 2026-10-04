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

        if (input[0] == '\0')
            continue;

        int result = handle_builtin(input);

        if (result == 1)
            break;

        if (result == 0)
            continue;

        execute_command(input);
    }

    return 0;
}
