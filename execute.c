#include "main.h"

int execute_cmd(char **args)
{
    char *cmd_path;
    int status;

    if (args[0] == NULL)
        return (0);

    if (is_builtin(args))
        return (0);

    cmd_path = resolve_cmd_path(args[0]);
    if (cmd_path == NULL)
    {
        fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
        return (127);
    }

    status = run_cmd(cmd_path, args);
    free(cmd_path);
    return (status);
}

int run_cmd(char *cmd_path, char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (execve(cmd_path, args, environ) == -1)
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
            free(cmd_path);
            exit(127);
        }
    }
    else if (pid < 0)
    {
        perror("fork");
        return (1);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            status = WEXITSTATUS(status);
        else
            status = 1;
    }

    return (status);
}

int is_builtin(char **args)
{
    if (strcmp(args[0], "env") == 0)
    {
        int i = 0;
        while (environ[i])
            printf("%s\n", environ[i++]);
        return (1);
    }
    return (0);
}

int handle_exit(char **args, char *line, int last_status)
{
    int status = last_status;
    if (args[1])
        status = atoi(args[1]);

    free(line);
    free(args);
    exit(status);
}
