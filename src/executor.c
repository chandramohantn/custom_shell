#include "../include/parser.h"
#include "../include/executor.h"
#include "../include///io_redirection.h"
#include "../include/builtin_commands.h"

void execute_command(char **command_list)
{
    if (check_command_in_builtin_list(command_list[0]))
    {
        execute_builtin_commands(command_list);
        return;
    }

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
        handle_io_redirection(command_list);
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

void execute_pipe_command(char *input)
{
    int fd[2];
    pid_t pid;
    int in_fd = STDIN_FILENO;
    char *command;
    command = strtok(input, PIPE_DELIMITER);

    while (command != NULL)
    {
        pipe(fd);
        pid = fork();
        int status;
        if (pid < 0)
        {
            perror("Unable to fork\n");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Creates a copy of the file descriptor
            dup2(in_fd, STDIN_FILENO);
            if (strtok(NULL, PIPE_DELIMITER) != NULL)
            {
                dup2(fd[1], STDOUT_FILENO);
            }
            close(fd[0]);
            close(fd[1]);

            char **command_list;
            command_list = parse_input(command);
            handle_io_redirection(command_list);
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
            close(fd[1]);
            in_fd = fd[0];
            command = strtok(NULL, PIPE_DELIMITER);
        }
    }
}
