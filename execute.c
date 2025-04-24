#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/**
 * run_command - Forks and executes the command passed in argv
 * @argv: array of strings, where argv[0] is the command
 * @line: the original input line to be freed after use
 */
int run_command(char **argv, char *line)
{
	pid_t pid;
	int status;
	char *cmd_path;

	if (!argv || !argv[0])
	{
		free(line);
		return (0);
	}

	if (argv[0][0] == '/' || (argv[0][0] == '.' && (argv[0][1] == '/' || argv[0][1] == '.')))
	{
		pid = fork();
		if (pid == 0)
		{
			execve(argv[0], argv, environ);
			perror(argv[0]);
			exit(2);  /* use 2 if command fails */
		}
		else if (pid > 0)
			wait(&status);
		else
		{
			perror("fork");
			free(line);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		cmd_path = search_path(argv[0]);
		if (!cmd_path)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
			free(line);
			return (127);
		}

		pid = fork();
		if (pid == 0)
		{
			execve(cmd_path, argv, environ);
			perror(cmd_path);
			free(cmd_path);
			exit(2);  /* use 2 for command fail */
		}
		else if (pid > 0)
		{
			wait(&status);
			free(cmd_path);
		}
		else
		{
			perror("fork");
			free(cmd_path);
			free(line);
			exit(EXIT_FAILURE);
		}
	}

	return (WEXITSTATUS(status));
}
