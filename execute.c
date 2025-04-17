#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * run_command - Executes a command with arguments
 * @argv: tokenized input
 * @line: original input line (to free after use)
 */
void run_command(char **argv, char *line)
{
	pid_t pid;
	int status;
	char *cmd_path;

	pid = fork();
	if (pid == 0)
	{
		cmd_path = search_path(argv[0]);
		if (!cmd_path)
		{
			perror("./hsh");
			exit(EXIT_FAILURE);
		}
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
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	free(line);
}
