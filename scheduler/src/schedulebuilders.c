#include "schedulebuilders.h"

// Can't use pow...
int rm_least_upper_bound(taskset_t* taskset){
    return -1;
    // float util = 0;
    // for(int i = 0; i < taskset->length; i++){
    //     util += (float) taskset->tasks[i].execution_time / taskset->tasks[i].period;
    // }
    // float bound = taskset->length * (pow(2, (float)1 / taskset->length) - 1);
    // P("Utilization: %f\n", util);
    // P("Bound: %f\n", bound);
    // return (util <= bound);
}

int rm_hyperbolic_bound(taskset_t* taskset){
    float util = 0;
    for(int i = 0; i < taskset->length; i++){
        util *= ((float) taskset->tasks[i].execution_time / taskset->tasks[i].period + 1);
    }
    P("Product: %f\n", util);
    return (util <= 2);
}

int rm_response_time_analysis(taskset_t* taskset){
    return 0;
}

schedule_t* edf_scheduler(taskset_t* taskset){
    return NULL;
}

schedule_t* rm_scheduler(taskset_t* taskset){
    return NULL;
}