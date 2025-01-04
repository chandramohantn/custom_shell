#include "../include/shell.h"
#include "../include/parser.h"
#include "../include/executor.h"
#include "../include/signal_handler.h"
#include "../include/job_control.h"

int main()
{
    char *command;
    bool is_background_process;

    signal(SIGINT, handle_sigint);
    signal(SIGTSTP, handle_sigtstp);

    while (1)
    {
        command = read_input();

        if (strcmp(command, "\n") == 0)
            continue;

        if (strncmp(command, "jobs", 4) == 0)
            list_jobs();
        else if (strncmp(command, "fg", 2) == 0)
        {
            int job_id = atoi(&command[3]);
            bring_job_to_foreground(job_id);
        }
        else if (strncmp(command, "bg", 2) == 0)
        {
            int job_id = atoi(&command[3]);
            bring_job_to_background(job_id);
        }

        if (is_pipe_present(command))
        {
            execute_pipe_command(command);
        }
        else
        {
            char **command_list;
            command_list = parse_input(command, &is_background_process);
            if (command_list[0] != NULL)
            {
                execute_command(command_list, command, is_background_process);
                is_background_process = false;
            }
            free(command_list);
        }
    }

    return 0;
}