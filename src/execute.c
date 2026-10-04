#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_command(char *input)
{
    char *pipe_position = strchr(input, '|');

    if (pipe_position != NULL)
    {
        *pipe_position = '\0';

        char *left_command = input;
        char *right_command = pipe_position + 1;

        char *left_args[64];
        char *right_args[64];

        int i = 0;
        int j = 0;

        char *token = strtok(left_command, " \t");

        while (token != NULL && i < 63)
        {
            left_args[i++] = token;
            token = strtok(NULL, " \t");
        }

        left_args[i] = NULL;

        token = strtok(right_command, " \t");

        while (token != NULL && j < 63)
        {
            right_args[j++] = token;
            token = strtok(NULL, " \t");
        }

        right_args[j] = NULL;

        if (left_args[0] == NULL || right_args[0] == NULL)
        {
            fprintf(stderr, "Syntax error: invalid pipe\n");
            return;
        }

        int pipefd[2];

        if (pipe(pipefd) == -1)
        {
            perror("pipe failed");
            return;
        }

        pid_t first_pid = fork();

        if (first_pid < 0)
        {
            perror("fork failed");
            return;
        }

        if (first_pid == 0)
        {
            close(pipefd[0]);

            dup2(pipefd[1], STDOUT_FILENO);

            close(pipefd[1]);

            execvp(left_args[0], left_args);

            perror("command execution failed");
            _exit(1);
        }

        pid_t second_pid = fork();

        if (second_pid < 0)
        {
            perror("fork failed");
            return;
        }

        if (second_pid == 0)
        {
            close(pipefd[1]);

            dup2(pipefd[0], STDIN_FILENO);

            close(pipefd[0]);

            execvp(right_args[0], right_args);

            perror("command execution failed");
            _exit(1);
        }

        close(pipefd[0]);
        close(pipefd[1]);

        waitpid(first_pid, NULL, 0);
        waitpid(second_pid, NULL, 0);

        return;
    }

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

            dup2(fd, STDIN_FILENO);
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

            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        execvp(args[0], args);

        perror("command execution failed");
        _exit(1);
    }

    waitpid(pid, NULL, 0);
}
