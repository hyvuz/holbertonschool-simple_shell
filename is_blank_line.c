#include "main.h"

/**
 * is_blank_line - Checks if the input line is empty or only spaces/tabs
 * @line: input string
 * Return: 1 if blank, 0 otherwise
*/
int is_blank_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}
