#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "shell.h"

void execute_command(char **command_list, char *command, bool is_background_process);
void execute_pipe_command(char *command);

#endif
