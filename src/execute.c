#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_command(char *input)
{
    char *args[64];
    int i = 0;

    char *token = strtok(input, " ");

    while (token != NULL && i < 63)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }

    args[i] = NULL;

    if (args[0] == NULL)
        return;

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return;
    }

    if (pid == 0)
    {
        execvp(args[0], args);

        perror("command execution failed");
        _exit(1);
    }
    else
    {
        waitpid(pid, NULL, 0);
    }
}
