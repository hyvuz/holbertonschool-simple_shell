#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctype.h>

/* Function Prototypes */
int is_blank_line(char *line);
char *get_input(void);
char **parse_input(char *input);
char *find_path(char *command);
int execute_command(char **args, char *argv0);
int check_builtins(char **args);
void free_args(char **args);

extern char **environ;

#endif /* MAIN_H */
