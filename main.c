#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "

extern char **environ; /* Environment variables for execve */

/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0 on success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int status;

	while (1)
	{
		/* Display prompt only in interactive mode */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

		/* Read user input */
		read = getline(&line, &len, stdin);

		/* Handle EOF (Ctrl+D) */
		if (read == -1)
		{
			free(line);
			exit(0);
		}

		/* Remove newline at the end */
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		/* Skip empty lines */
		if (line[0] == '\0')
			continue;

		pid = fork();
		if (pid == 0)
		{
			/* Child process */
			char *argv[2];

			argv[0] = line;
			argv[1] = NULL;

			if (execve(line, argv, environ) == -1)
			{
				perror("./hsh");
				exit(EXIT_FAILURE);
			}
		}
		else if (pid > 0)
		{
			/* Parent process waits for child */
			wait(&status);
		}
		else
		{
			/* Fork error */
			perror("fork");
			exit(EXIT_FAILURE);
		}
	}

	free(line);
	return (0);
}
