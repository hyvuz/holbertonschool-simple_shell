#include "main.h"

/**
 * check_builtins - Checks for built-in commands
 * @args: Array of command arguments
 *
 * Return: 1 if built-in command was executed, 0 otherwise
*/
int check_builtins(char **args)
{
if (strcmp(args[0], "exit") == 0)
{
exit(0);
}
else if (strcmp(args[0], "env") == 0)
{
char **env = environ;
while (*env)
{
printf("%s\n", *env);
env++;
}
return (1);
}
/* Add more built-ins here as needed */
return (0);
}

/**
 * execute_command - Executes a command
 * @args: Array of arguments
 * @argv0: Program name for error messages
 *
 * Return: 1 on success, -1 on failure
*/
int execute_command(char **args, char *argv0)
{
/* Existing execute_command implementation */
char *path = find_path(args[0]);
pid_t pid;
int status;

if (!path)
{
fprintf(stderr, "%s: 1: %s: not found\n", argv0, args[0]);
return (-1);
}

pid = fork();
if (pid == 0)
{
if (execve(path, args, environ) == -1)
{
perror(argv0);
free(path);
exit(EXIT_FAILURE);
}
}
else if (pid < 0)
{
perror(argv0);
free(path);
return (-1);
}
else
{
wait(&status);
free(path);
}

return (1);
}
