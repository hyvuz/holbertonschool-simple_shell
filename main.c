#include "main.h"

/**
 * main - entry point for the shell
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    (void)ac;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(1, "#cisfun$ ", 9);

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            free(line);
            exit(0);
        }

        line[nread - 1] = '\0';

        if (_strlen(line) == 0)
            continue;

        pid = fork();
        if (pid == 0)
        {
            char *argv[2];
            argv[0] = line;
            argv[1] = NULL;

            if (execve(line, argv, environ) == -1)
            {
                perror(av[0]);
                exit(1);
            }
        }
        else if (pid > 0)
            wait(NULL);
        else
            perror("fork failed");
    }

    free(line);
    return (0);
}
