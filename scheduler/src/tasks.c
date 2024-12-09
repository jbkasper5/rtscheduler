#include "tasks.h"

void print_task(task_t* task){
    printf("Task:\n");
    printf("\tType:             %u\n", task->type);
    printf("\tExecution time:   %.3f\n", task->execution_time);
    printf("\tPeriod:           %.3f\n", task->period);
    printf("\tRefresh:          %.3f\n", task->refresh);
    printf("\tDeadline:         %.3f\n", task->deadline);
    printf("\tOffset:           %.3f\n", task->offset);
}