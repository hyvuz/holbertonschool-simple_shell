#include "main.h"

int main(int argc, char **argv)
{
char *line = NULL;
char **args = NULL;
int status;
(void)argc;

while (1)
{
if (isatty(STDIN_FILENO))
printf(":) ");

line = get_input();
if (!line)
break;

if (is_blank_line(line))
{
free(line);
continue;
}

args = parse_input(line);
if (!args[0])
{
free_args(args);
free(line);
continue;
}

status = check_builtins(args);
if (status == 0)
status = execute_command(args, argv[0]);

free_args(args);
free(line);
}
return (0);
}
