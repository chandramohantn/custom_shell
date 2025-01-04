#include "../include/shell.h"
#include "../include/parser.h"
#include "../include/executor.h"

int main()
{
    char *command;
    bool is_background_process;

    while (1)
    {
        command = read_input();
        char **command_list;
        command_list = parse_input(command);
        execute_command(command_list);
    }

    return 0;
}