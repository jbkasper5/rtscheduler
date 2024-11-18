#include <pthread.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sigint_handler(int signum);
void sigusr_handler(int signum);

void* add_task(void* arg);
void task(unsigned long execution_time);
void task_manager(void);