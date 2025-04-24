void run_command(char **argv, char *line)
{
    pid_t pid;
    int status;
    char *cmd_path;

    if (!argv || !argv[0])
    {
        free(line);
        return;
    }

    /* 🔥 Built-in: exit */
    if (strcmp(argv[0], "exit") == 0)
    {
        free(line);
        exit(0);
    }

    if (argv[0][0] == '/' || (argv[0][0] == '.' && (argv[0][1] == '/' || argv[0][1] == '.')))
    {
        if (execve(argv[0], argv, environ) == -1)
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
            free(line);
            exit(127);
        }
    }
    else
    {
        cmd_path = search_path(argv[0]);
        if (!cmd_path)
        {
            fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
            free(line);
            exit(127);
        }

        if (execve(cmd_path, argv, environ) == -1)
        {
            perror("./hsh");
            free(cmd_path);
            free(line);
            exit(EXIT_FAILURE);
        }
        free(cmd_path);
    }

    wait(&status);
    free(line);
}
