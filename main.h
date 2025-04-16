#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <ctype.h>

/* Global environment */
extern char **environ;

/* Function prototypes */
char **parse_input(char *input);
char *find_path(char *command);
int execute_command(char **args, char *argv0);
int check_builtins(char **args);
void free_args(char **args);
char *get_input(void);
char *get_env_var(const char *name);
char *find_command_in_path(char *command);

#endif /* MAIN_H */
