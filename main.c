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
	int last_status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

		line = read_input();
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		parse_input(line, argv);

		if (argv[0] == NULL)
		{
			free(line);
			continue;
		}

		/* exit should return last_status */
		if (strcmp(argv[0], "exit") == 0)
		{
			free(line);
			exit(last_status);
		}

		last_status = run_command(argv, line);
		free(line);
	}

	return (0);
}

	return (0);
}
