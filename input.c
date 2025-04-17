#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * read_input - Reads a line from stdin
 * Return: pointer to the input line, or NULL on empty input
 */
char *read_input(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	read = getline(&line, &len, stdin);

	if (read == -1)
	{
		free(line);
		exit(0);
	}

	if (line[read - 1] == '\n')
		line[read - 1] = '\0';

	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}

	return (line);
}
