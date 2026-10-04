#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

int handle_builtin(char *input)
{
    if (strcmp(input, "exit") == 0)
    {
        printf("Exiting ShellForge...\n");
        return 1;
    }

    if (strcmp(input, "pwd") == 0)
    {
        char cwd[PATH_MAX];

        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s\n", cwd);
        }
        else
        {
            perror("pwd failed");
        }

        return 0;
    }

    if (strcmp(input, "cd") == 0)
    {
        printf("Usage: cd <directory>\n");
        return 0;
    }

    if (strncmp(input, "cd ", 3) == 0)
    {
        char *directory = input + 3;

        if (chdir(directory) != 0)
        {
            perror("cd failed");
        }

        return 0;
    }

    return -1;
}
