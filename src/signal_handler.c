#include "../include/shell.h"

void handle_sigint()
{
    if (tcgetpgrp(STDIN_FILENO) != getpid())
    {
        kill(-tcgetpgrp(STDIN_FILENO), SIGINT);
    }
}

void handle_sigtstp()
{
    if (tcgetpgrp(STDIN_FILENO) != getpid())
    {
        kill(-tcgetpgrp(STDIN_FILENO), SIGTSTP);
    }
}
