#include <stdlib.h>
#include "tasks.h"

#define TRUE    1
#define FALSE   0

task_t* task_init(){
    task_t* task = malloc(sizeof(task));
    task->type = periodic;
    task->execution_time = 0;
    task->period = 0;
    task->refresh = 0;
    task->deadline = 0;
    task->offset = 0;
    task->priority = 0;
    return task;
}

taskset_t* taskset_init(){
    taskset_t* taskset = malloc(sizeof(taskset_t));
    taskset->length = 0;
    taskset->tasks = NULL;
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

void task_destroy(task_t* task){
    if(!task) return;
    free(task);
}

void taskset_destroy(taskset_t* taskset){
    if(!taskset) return;
    for(int i = 0; i < taskset->length; i++){
        task_destroy(taskset->tasks + i);
    }
    if(taskset->schedule) schedule_destroy(taskset->schedule);
    free(taskset);
}

void schedule_destroy(schedule_t* schedule){
    if(!schedule) return;
    if(schedule->schedule) free(schedule->schedule);
    free(schedule);
}