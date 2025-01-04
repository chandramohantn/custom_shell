#ifndef JOB_CONTROL_H
#define JOB_CONTROL_H

#include "shell.h"

typedef enum
{
    RUNNING,
    STOPPED
} job_status;
typedef struct
{
    pid_t pgid;
    job_status status;
    char command[BUFFER_SIZE];
} Job;

bool check_if_job_table_is_full(int count);
bool check_if_job_table_is_empty(int count);
void add_job(Job job);
void list_jobs(void);
void bring_job_to_foreground(int job_id);
void bring_job_to_background(int job_id);

#endif
