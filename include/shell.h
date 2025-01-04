#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/types.h>
#include <signal.h>

#define BUFFER_SIZE 1024
#define NUMBER_OF_JOBS 100
#define TOKEN_DELIMITER " \t\n\r\a"
#define PIPE_DELIMITER "|"

#endif