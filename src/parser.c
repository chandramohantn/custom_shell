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

char **tokenize(char *command, int *token_count)
{
    int position;
    char **tokens, *token;
    tokens = (char **)malloc(BUFFER_SIZE * sizeof(char *));
    *token_count = 0;

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
        *token_count += 1;
    }
    tokens[position] = NULL;
    return tokens;
}

char **parse_input(char *command, bool *is_background_process)
{
    int token_count;
    char **command_list;
    *is_background_process = false;
    command_list = tokenize(command, &token_count);
    if (strcmp(command_list[token_count - 1], "&") == 0)
    {
        *is_background_process = true;
    }
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
