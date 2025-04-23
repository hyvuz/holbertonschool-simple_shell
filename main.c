#include "main.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **args;
    int status = 0;

    while (1)
    {
        print_prompt();

        read = read_line(&line, &len);
        if (read == -1)
        {
            free(line);
            exit(status);
        }

        args = parse_line(line);
        if (args && args[0] != NULL)
        {
            if (strcmp(args[0], "exit") == 0)
                handle_exit(args, line, status);
            else
                status = execute_cmd(args);
        }

        free(args);
        free(line);
        line = NULL;
        len = 0;
    }

    return (status);
}
