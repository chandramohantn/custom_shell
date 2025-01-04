#include "../include/builtin_commands.h"

const char *builtin_command_list[] = {"exit", "cd"};
const int builtin_command_count = sizeof(builtin_command_list) / sizeof(builtin_command_list[0]);

void execute_exit()
{
    printf("Exiting learner shell\n");
    exit(EXIT_SUCCESS);
}

void execute_cd(char **command_list)
{
    if (command_list[1] == NULL)
    {
        perror("No arguments provided for cd\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        if (chdir(command_list[1]) != 0)
        {
            perror("Not a valid directory\n");
        }
    }
}

bool check_command_in_builtin_list(char *command)
{
    for (int index = 0; index < builtin_command_count; index++)
    {
        if (strcmp(builtin_command_list[index], command) == 0)
        {
            return true;
        }
    }
    return false;
}

void execute_builtin_commands(char **command_list)
{
    if (strcmp("exit", command_list[0]) == 0)
    {
        if (command_list[1] == NULL)
        {
            execute_exit();
        }
        else
        {
            perror("No arguments required for exit command\n");
        }
    }
    else if (strcmp("cd", command_list[0]) == 0)
    {
        execute_cd(command_list);
    }
}
