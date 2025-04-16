#include "main.h"

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
