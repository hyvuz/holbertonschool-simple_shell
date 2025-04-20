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
	char *cmd_path = NULL;

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
			/* check if command is a direct path */
			if (argv[0][0] == '/' || (argv[0][0] == '.' && (argv[0][1] == '/' || (argv[0][1] == '.' && argv[0][2] == '/'))))
			{
				cmd_path = argv[0];
			}
			else
			{
				fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
				exit(127);
			}
		}

		if (execve(cmd_path, argv, environ) == -1)
		{
			perror("./hsh");
			if (cmd_path != argv[0]) /* Only free if it was allocated */
				free(cmd_path);
			exit(127);
		}
	}
	else if (pid > 0)
	{
		wait(&status);
		last_exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : EXIT_FAILURE;
	}
	else
	{
		perror("fork");
		free(line);
		exit(EXIT_FAILURE);
	}

	free(line);
	if (cmd_path && cmd_path != argv[0])
		free(cmd_path);
}
