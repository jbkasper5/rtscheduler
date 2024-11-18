#include "taskmanager.h"

void sigint_handler(int signum){
    printf("Process '%d' received SIGINT\n", getpid());
}

void sigusr_handler(int signum){
    printf("Process '%d' received SIGUSR1\n", getpid());
}

void task_manager(void){
    pid_t parent = getppid();
    printf("Child: initializing signal handlers\n");
    signal(SIGUSR1, sigusr_handler);
    signal(SIGINT, sigint_handler);
    
    printf("Child: signal handlers initialized, ready for tasks\n");
    kill(parent, SIGUSR2);
    pause();
    pthread_t ptid; 

    // Creating a new thread 
    pthread_create(&ptid, NULL, &add_task, NULL); 
    // Waiting for the created thread to terminate 
    pthread_join(ptid, NULL);
    
    // task manager dies once all tasks have been scheduled
    exit(0);
}


void* add_task(void* arg){ 
    printf("Task thread\n"); 

    // exit the current thread 
    pthread_exit(NULL); 
} 


// function to spin a task for it's execution time
void task(unsigned long execution_time){
    printf("Executing task...\n");
}