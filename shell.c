#include "main.h"

/**
 * main - Entry point for the simple shell program
 * @argc: Argument count (unused)
 * @argv: Argument vector (for program name)
 *
 * Return: Always 0 (success)
*/
int main(int argc, char **argv)
{
char *line = NULL;
char **args;
int status;
(void)argc; /* Unused parameter */

do {
/* Print prompt if in interactive mode */
if (isatty(STDIN_FILENO))
printf(":) ");

line = get_input();
if (!line)
break;

args = parse_input(line);
if (!args[0])
{
free_args(args);
continue;
}

/* Check for built-in commands */
status = check_builtins(args);
if (status == 0) /* Not a built-in */
status = execute_command(args, argv[0]);

free_args(args);
free(line);
} while (status >= 0);

return (0);
}

/**
 * get_input - Reads input from stdin
 *
 * Return: Pointer to the input string, or NULL on failure
*/
char *get_input(void)
{
char *line = NULL;
size_t len = 0;
ssize_t read;

read = getline(&line, &len, stdin);
if (read == -1)
{
free(line);
return (NULL);
}

/* Remove trailing newline */
if (line[read - 1] == '\n')
line[read - 1] = '\0';

return (line);
}
