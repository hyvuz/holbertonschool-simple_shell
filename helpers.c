#include "main.h"
/**
 * is_blank_line - Checks if line contains only whitespace
 * @line: Input string to check
 * Return: 1 if blank, 0 otherwise
*/
int is_blank_line(char *line)
{
if (!line) return (1);

while (*line) {
if (!isspace(*line) && *line != '\n')
return (0);
line++;
}
return (1);
}
/**
 * parse_input - Parses input string into arguments
 * @input: The input string to parse
 *
 * Return: Array of arguments (NULL-terminated)
*/
char **parse_input(char *input)
{
int bufsize = 64, position = 0;
char **tokens = malloc(bufsize * sizeof(char *));
char *token;

if (!tokens)
{
fprintf(stderr, "Allocation error\n");
exit(EXIT_FAILURE);
}

token = strtok(input, " ");
while (token)
{
tokens[position] = token;
position++;

if (position >= bufsize)
{
bufsize += 64;
tokens = realloc(tokens, bufsize * sizeof(char *));
if (!tokens)
{
fprintf(stderr, "Allocation error\n");
exit(EXIT_FAILURE);
}
}

token = strtok(NULL, " ");
}
tokens[position] = NULL;
return (tokens);
}

/**
 * free_args - Frees memory allocated for arguments array
 * @args: Array of arguments to free
*/
void free_args(char **args)
{
free(args);
}
/**
 * get_input - Reads a line of input from stdin
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
