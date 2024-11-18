#include "scheduler.h"

void signal_tm_ready(int signum){
    printf("Parent process '%d' received SIGUSR2\n", getpid());
}

void scheduler(void){
    // set up handler so the parent knows when the task manager is ready
    signal(SIGUSR2, signal_tm_ready);

    // fork the process
    pid_t pid = fork();

    // child process becomes the task manager on a different core
    if(pid == 0){
        printf("Child process, executing task manager...\n");
        task_manager();
    }

    // wait for task manager process to signal that it's ready
    pause();
    printf("Parent process: supplying tasks.\n");
    // signal to the task manager
    kill(pid, SIGUSR1);
    kill(pid, SIGINT);

    // wait for TM to finish
    wait(&pid);
    printf("Child died.\n");
}