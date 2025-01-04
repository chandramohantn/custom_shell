#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "shell.h"

void execute_command(char **command);
void execute_pipe_command(char *command);

#endif
