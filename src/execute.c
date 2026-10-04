#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_command(char *input)
{
    char *args[64];
    int i = 0;

    char *input_file = NULL;
    char *output_file = NULL;

    int append = 0;
    int input_redirect = 0;
    int output_redirect = 0;

    char *token = strtok(input, " \t");

    while (token != NULL && i < 63)
    {
        if (strcmp(token, "<") == 0)
        {
            input_redirect = 1;

            token = strtok(NULL, " \t");

            if (token == NULL)
            {
                fprintf(stderr, "Syntax error: missing input file\n");
                return;
            }

            input_file = token;
        }
        else if (strcmp(token, ">") == 0)
        {
            output_redirect = 1;
            append = 0;

            token = strtok(NULL, " \t");

            if (token == NULL)
            {
                fprintf(stderr, "Syntax error: missing output file\n");
                return;
            }

            output_file = token;
        }
        else if (strcmp(token, ">>") == 0)
        {
            output_redirect = 1;
            append = 1;

            token = strtok(NULL, " \t");

            if (token == NULL)
            {
                fprintf(stderr, "Syntax error: missing output file\n");
                return;
            }

            output_file = token;
        }
        else
        {
            args[i++] = token;
        }

        token = strtok(NULL, " \t");
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
        if (input_redirect)
        {
            int fd = open(input_file, O_RDONLY);

            if (fd < 0)
            {
                perror("input file open failed");
                _exit(1);
            }

            if (dup2(fd, STDIN_FILENO) < 0)
            {
                perror("dup2 failed");
                close(fd);
                _exit(1);
            }

            close(fd);
        }

        if (output_redirect)
        {
            int flags = O_WRONLY | O_CREAT;

            if (append)
                flags |= O_APPEND;
            else
                flags |= O_TRUNC;

            int fd = open(output_file, flags, 0644);

            if (fd < 0)
            {
                perror("output file open failed");
                _exit(1);
            }

            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                perror("dup2 failed");
                close(fd);
                _exit(1);
            }

            close(fd);
        }

        execvp(args[0], args);

        perror("command execution failed");
        _exit(1);
    }

    waitpid(pid, NULL, 0);
}
