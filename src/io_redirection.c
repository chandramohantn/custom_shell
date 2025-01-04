#include "../include/io_redirection.h"

void handle_io_redirection(char **command_list)
{
    int index = 0;
    while (command_list[index] != NULL)
    {
        if (strcmp(command_list[index], ">") == 0)
        {
            int fd = open(command_list[index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                perror("Unable to create file descriptor\n");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            command_list[index] = NULL;
        }
        else if (strcmp(command_list[index], ">>") == 0)
        {
            int fd = open(command_list[index + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                perror("Unable to create file descriptor\n");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            command_list[index] = NULL;
        }
        else if (strcmp(command_list[index], "<") == 0)
        {
            int fd = open(command_list[index + 1], O_RDONLY);
            if (fd == -1)
            {
                perror("Unable to create file descriptor\n");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            command_list[index] = NULL;
        }
        index = index + 1;
    }
}
