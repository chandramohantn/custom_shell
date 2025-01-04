#include "../include/parser.h"

char *read_input(void)
{
    char *buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
    if (!buffer)
    {
        perror("Unable to allocate buffer memory\n");
        exit(EXIT_FAILURE);
    }
    printf("learner> ");
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
    {
        free(buffer);
        exit(EXIT_SUCCESS);
    }
    return buffer;
}

char **tokenize(char *command)
{
    int position;
    char **tokens, *token;
    tokens = (char **)malloc(BUFFER_SIZE * sizeof(char *));

    if (!tokens)
    {
        perror("Unable to allocate buffer memory");
        exit(EXIT_FAILURE);
    }

    position = 0;
    token = strtok(command, TOKEN_DELIMITER);
    while (token != NULL)
    {
        tokens[position] = token;
        position = position + 1;
        token = strtok(NULL, TOKEN_DELIMITER);
    }
    tokens[position] = NULL;
    return tokens;
}

char **parse_input(char *command)
{
    char **command_list;
    command_list = tokenize(command);
    return command_list;
}

bool is_pipe_present(char *command)
{
    if (strstr(command, PIPE_DELIMITER) != NULL)
    {
        return true;
    }
    return false;
}
