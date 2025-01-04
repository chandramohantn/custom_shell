#ifndef BUILTIN_COMMANDS_H
#define BUILTIN_COMMANDS_H

#include "shell.h"

extern const char *builtin_command_list[];
extern const int builtin_command_count;

void execute_builtin_commands(char **command_list);
void execute_exit(void);
void execute_cd(char **command);
bool check_command_in_builtin_list(char *command);

#endif