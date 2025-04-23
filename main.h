#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

char **parse_line(char *line);
char *read_input(void);
int execute_cmd(char **args);
int is_builtin(char **args);
int handle_exit(char **args, char *line, int last_status);
char *resolve_cmd_path(char *cmd);
char *find_command(char *command);
int run_cmd(char *cmd_path, char **args);
void print_prompt(void);
ssize_t read_line(char **line, size_t *len);

#endif /* MAIN_H */
