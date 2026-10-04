#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/shell.h"
#include "../include/input.h"
#include "../include/parser.h"
#include "../include/process.h"
#include "../include/builtin.h"
#include "../include/signals.h"
#include "../include/pipes.h"

static void tokenize(char *str, char **argv)
{
    int i = 0;

    char *token = strtok(str, " \t\n");

    while (token != NULL)
    {
        argv[i++] = token;
        token = strtok(NULL, " \t\n");
    }

    argv[i] = NULL;
}

int main()
{
    char *line;
    char **tokens;

    initialize_signals();

    printf("=====================================\n");
    printf("ShellForge Version 7.0\n");
    printf("=====================================\n");

    while (1)
    {
        printf("myshell> ");
        fflush(stdout);

        line = read_line();

        if (strcmp(line, "exit") == 0)
        {
            free(line);
            break;
        }

        if (strchr(line, '|') != NULL)
        {
            char *argv1[64];
            char *argv2[64];

            char *left = strtok(line, "|");
            char *right = strtok(NULL, "|");

            if (left == NULL || right == NULL)
            {
                printf("Invalid pipe command\n");
                free(line);
                continue;
            }

            tokenize(left, argv1);
            tokenize(right, argv2);

            if (argv1[0] != NULL && argv2[0] != NULL)
            {
                execute_pipe(argv1, argv2);
            }
        }
        else
        {
            tokens = parse_line(line);

            if (tokens[0] != NULL)
            {
                if (execute_builtin(tokens) == 0)
                {
                    execute(tokens);
                }
            }

            free_tokens(tokens);
        }

        free(line);
    }

    return 0;
}
