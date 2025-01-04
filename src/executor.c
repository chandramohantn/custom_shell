#include "../include/executor.h"

void execute_command(char **command_list)
{
    pid_t pid;
    pid = fork();
    int status;

    if (pid < 0)
    {
        perror("Unable to fork\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (execvp(command_list[0], command_list) == -1)
        {
            perror("Unable to execute the command\n");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}
