#include <string.h>

/**
 * parse_input - Splits input into tokens (command + args)
 * @line: input line
 * @argv: output array of tokens
 */
void parse_input(char *line, char **argv)
{
	char *token;
	int i = 0;

	token = strtok(line, " ");
	while (token != NULL)
	{
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;
}
