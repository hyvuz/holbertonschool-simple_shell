#include "main.h"

/**
 * get_env_var - Gets an environment variable
 * @name: Name of the environment variable
 *
 * Return: Value of the variable or NULL if not found
*/
char *get_env_var(const char *name)
{
int i;
size_t len = strlen(name);

for (i = 0; environ[i]; i++)
{
if (strncmp(name, environ[i], len) == 0 && environ[i][len] == '=')
return (&environ[i][len + 1]);
}

return (NULL);
}

/**
 * find_path - Locates the full path of a command
 * @command: The command to locate
 *
 * Return: Full path of the command if found, NULL otherwise
*/
char *find_path(char *command)
{
char *path = get_env_var("PATH");
char *path_copy, *dir, *full_path;
struct stat st;

if (!path)
return (NULL);

path_copy = strdup(path);
if (!path_copy)
return (NULL);

dir = strtok(path_copy, ":");
while (dir)
{
full_path = malloc(strlen(dir) + strlen(command) + 2);
if (!full_path)
{
free(path_copy);
return (NULL);
}

sprintf(full_path, "%s/%s", dir, command);

if (stat(full_path, &st) == 0)
{
free(path_copy);
return (full_path);
}

free(full_path);
dir = strtok(NULL, ":");
}

free(path_copy);
return (NULL);
}
