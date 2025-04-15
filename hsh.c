#include "main.h"

/**
 * main - Simple shell loop
 *
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	char *args[64];
	int i;
	pid_t pid;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);

		if (getline(&line, &len, stdin) == -1)
			break;

		if (line[0] == '\n')
			continue;

		if (_strcmp(line, "exit\n") == 0)
			break;

		args[0] = strtok(line, " \n");
		i = 1;
		while ((args[i] = strtok(NULL, " \n")) != NULL)
			i++;

		pid = fork();
		if (pid == 0)
		{
			if (execvp(args[0], args) == -1)
				perror("hsh");
			exit(1);
		}
		else
			wait(NULL);
	}
	free(line);
	return (0);
}
