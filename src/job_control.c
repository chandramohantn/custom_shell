#include "../include/job_control.h"

Job job_table[NUMBER_OF_JOBS];
static int job_count = 0;

bool check_if_job_table_is_full(int count)
{
    if (count >= NUMBER_OF_JOBS)
    {
        return true;
    }
    return false;
}

bool check_if_job_table_is_empty(int count)
{
    if (count <= 0)
    {
        return true;
    }
    return false;
}

bool check_valid_job(int job_id)
{
    if (job_id <= 0 || job_id >= NUMBER_OF_JOBS)
    {
        return false;
    }
    return true;
}

void add_job(Job job)
{
    if (!check_if_job_table_is_full(job_count))
    {
        job_table[job_count] = job;
        job_count += 1;
    }
    else
    {
        perror("Job table full\n");
    }
}

void list_jobs(void)
{
    printf("Job ID\tPGID\tStatus\tCommand\n");
    for (int index = 0; index < job_count; index++)
    {
        printf("[%d]\t%d\t%s\t%s\n", index + 1, job_table[index].pgid, job_table[index].status == RUNNING ? "Running" : "Stopped", job_table[index].command);
    }
}

void bring_job_to_foreground(int job_id)
{
    if (check_valid_job(job_id))
    {
        Job *job = &job_table[job_id - 1];
        tcsetpgrp(STDIN_FILENO, job->pgid);
        kill(-job->pgid, SIGCONT);
        printf("Job moved to foreground\n");

        int status;
        waitpid(-job->pgid, &status, WUNTRACED);

        tcsetpgrp(STDIN_FILENO, getpid());
        if (WIFSTOPPED(status))
        {
            job->status = STOPPED;
        }
        else
        {
            for (int index = job_id - 1; index < job_count - 1; index++)
            {
                job_table[index] = job_table[index + 1];
            }
            job_count -= 1;
        }
    }
    else
    {
        perror("Not a valid job id\n");
    }
}

void bring_job_to_background(int job_id)
{
    if (check_valid_job(job_id))
    {
        Job *job = &job_table[job_id - 1];
        tcsetpgrp(STDIN_FILENO, job->pgid);
        kill(-job->pgid, SIGCONT);
        printf("Job moved to background\n");
    }
    else
    {
        perror("Not a valid job id\n");
    }
}
