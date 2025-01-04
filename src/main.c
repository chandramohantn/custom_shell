#include "../include/shell.h"
#include "../include/parser.h"
#include "../include/executor.h"
#include "../include/signal_handler.h"

int main()
{
    char *command;
    bool is_background_process;

    signal(SIGINT, handle_sigint);
    signal(SIGTSTP, handle_sigtstp);

    while (1)
    {
        command = read_input();
        if (is_pipe_present(command))
        {
            execute_pipe_command(command);
        }
        else
        {
            char **command_list;
            command_list = parse_input(command);
            execute_command(command_list);
        }
    }

    return 0;
}