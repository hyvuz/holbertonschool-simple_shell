#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "

/**
 * main - Entry point for the simple shell
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	char *argv[100];

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

		line = read_input();
		if (!line)
			continue;

		parse_input(line, argv);

		/* Built-in command: exit */
		if (argv[0] && strcmp(argv[0], "exit") == 0)
		{
			free(line);
			exit(0);
		}

		run_command(argv, line);
		free(line); /* Always free line after running a command */
	}

	return (0);
}
