#include "main.h"

char *resolve_cmd_path(char *cmd)
{
    char *cmd_path = NULL;

    if (strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
            cmd_path = strdup(cmd);
    }
    else
        cmd_path = find_command(cmd);

    return (cmd_path);
}

char *find_command(char *command)
{
    char *path = getenv("PATH");
    char *dir, *full_path;
    struct stat st;

    if (!path)
        return (NULL);

    path = strdup(path);
    dir = strtok(path, ":");

    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (!full_path)
            break;

        sprintf(full_path, "%s/%s", dir, command);

        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
        {
            free(path);
            return (full_path);
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path);
    return (NULL);
}
