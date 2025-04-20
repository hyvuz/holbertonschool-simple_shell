#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * run_command - Executes a command with its arguments
 * @argv: array of argument strings (argv[0] = command)
 * @line: the original input line (to be freed after use)
 *
 * Return: void
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

	pid = fork();
	if (pid == 0)
	{
		cmd_path = search_path(argv[0]);

		if (!cmd_path)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
			last_exit_status = 127;
			exit(127);
		}

		if (execve(cmd_path, argv, environ) == -1)
		{
			perror("./hsh");
			free(cmd_path);
			last_exit_status = EXIT_FAILURE;
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
			last_exit_status = WEXITSTATUS(status);
	}
	else
	{
		perror("fork");
		free(line);
		last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}

	free(line);
}
