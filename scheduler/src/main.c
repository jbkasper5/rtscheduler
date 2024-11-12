#include "scheduler.h"

int main(int argc, char** argv){
    taskset_t* set = taskset_init();
    schedule_t* schedule = edf_scheduler(set);
    if(schedule){
        printf("Task set is schedulable!\n");
        schedule_destroy(schedule);
    }else{
        printf("Task set is not schedulable.\n");
    }
    taskset_destroy(set);
    return 0;
}