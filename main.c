#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "

extern char **environ;

/**
 * main - A simple shell that supports command with arguments
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL, *token = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int status;
	char *argv[100]; /* array to hold arguments */
	int i;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			free(line);
			exit(0);
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		if (line[0] == '\0')
			continue;

		/* Tokenize input line */
		i = 0;
		token = strtok(line, " ");
		while (token != NULL)
		{
			argv[i++] = token;
			token = strtok(NULL, " ");
		}
		argv[i] = NULL;

		pid = fork();
		if (pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
			{
				perror("./hsh");
				exit(EXIT_FAILURE);
			}
		}
		else if (pid > 0)
		{
			wait(&status);
		}
		else
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
	}

	free(line);
	return (0);
}
