#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * search_path - Searches for a command in PATH
 * @command: the command name (e.g. "ls")
 * Return: full path if found (dynamically allocated), NULL if not found
 */
char *search_path(char *command)
{
	char *path, *dir, *full_path;
	char *path_copy;
	size_t len;

	if (access(command, X_OK) == 0)
		return (strdup(command)); /* Full path already */

	path = getenv("PATH");

	/* ✅ Fix: Handle both NULL and empty PATH */
	if (!path || *path == '\0')
		return (NULL);

	path_copy = strdup(path);
	dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
		len = strlen(dir) + strlen(command) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path); /* Found */
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL); /* Not found */
}
