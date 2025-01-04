#ifndef PARSER_H
#define PARSER_H

#include "shell.h"

char *read_input(void);
char **parse_input(char *command);
bool is_pipe_present(char *command);

#endif
