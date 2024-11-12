#include "tasks.h"

#define TRUE    1
#define FALSE   0

void print_task(task_t* task){
    printf("Task:\n");
    printf("\tType:             %u\n", task->type);
    printf("\tExecution time:   %.3f\n", task->execution_time);
    printf("\tPeriod:           %.3f\n", task->period);
    printf("\tRefresh:          %.3f\n", task->refresh);
    printf("\tDeadline:         %.3f\n", task->deadline);
    printf("\tOffset:           %.3f\n", task->refresh);
}

taskset_t* taskset_init(int num_tasks){
    taskset_t* taskset = malloc(sizeof(taskset_t));
    taskset->length = num_tasks;
    taskset->tasks = malloc(sizeof(task_t) * num_tasks);
    taskset->algorithm = RM;
    taskset->schedulable = FALSE;
    taskset->schedule = NULL;
    return taskset;
}

schedule_t* schedule_init(){
    schedule_t* schedule = malloc(sizeof(schedule_t));
    schedule->schedule = NULL;
    schedule->macrocycles = 0;
    schedule->microcycles = 0;
    return schedule;
}

void taskset_destroy(taskset_t* taskset){
    if(!taskset) return;
    free(taskset->tasks);
    if(taskset->schedule) schedule_destroy(taskset->schedule);
    free(taskset);
}

void schedule_destroy(schedule_t* schedule){
    if(!schedule) return;
    if(schedule->schedule) free(schedule->schedule);
    free(schedule);
}