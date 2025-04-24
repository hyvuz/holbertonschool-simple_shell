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

	/* Check if the command is a path (absolute or relative) */
	if (argv[0][0] == '/' || (argv[0][0] == '.' && (argv[0][1] == '/' || argv[0][1] == '.')))
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
			{
				fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
				exit(127);
			}
		}
		else if (pid > 0)
		{
			wait(&status);
		}
		else
		{
			perror("fork");
			free(line);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* This uses your own search_path() function */
		cmd_path = search_path(argv[0]);
		if (!cmd_path)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
			free(line);
			exit(127);
		}

		pid = fork();
		if (pid == 0)
		{
			if (execve(cmd_path, argv, environ) == -1)
			{
				perror("./hsh");
				free(cmd_path);
				exit(EXIT_FAILURE);
			}
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
}
