#include "scheduler.h"
#include "parser.h"

#define CFGPATH "/Users/jakekasper/Pitt/Pitt2024-25/Fall/AdvancedSoftware/project/rtscheduler/scheduler/taskset.cfg"

int main(int argc, char** argv){
    taskset_t* set = parse_taskset(CFGPATH);
    int schedulable = rm_least_upper_bound(set);
    printf("LUB test: %d\n", schedulable);
    for(int i = 0; i < set->length; i++){
        print_task(set->tasks + i);
    }
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