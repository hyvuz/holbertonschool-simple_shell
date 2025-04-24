#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>

extern char **environ;
char *search_path(char *command);
char *read_input(void);
void parse_input(char *line, char **argv);
void run_command(char **argv, char *line);

#endif /* MAIN_H */
