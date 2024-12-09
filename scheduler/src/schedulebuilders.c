#include "schedulebuilders.h"

// TODO: inefficient
float nth_pow(float x, int n) {
    float X = x;
    for (int i = 1; i < n; i++) {
        X *= x;
    }
    return X;
}

// https://en.wikipedia.org/wiki/Nth_root#Using_Newton's_method
// x^(1/n)
float nth_root(int x, int n) {
    float X[10] = { x / n, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // X_0 = initial guess
    for (int i = 0; i < 9; i++) {
        X[i + 1] = ((n - 1) * X[i] / n) + ((x / n) * (1 / nth_pow(X[i], n - 1)));
    }
    return X[9]; // hopefully 9 iterations is good enough
}

int rm_least_upper_bound(taskset_t* taskset){
    float util = 0;
    for(int i = 0; i < taskset->length; i++){
        util += (float) (taskset->tasks[i]->execution_time / taskset->tasks[i]->period);
    }
    float bound = taskset->length * (nth_root(2, taskset->length) - 1);
    printf("Utilization: %f\n", util);
    printf("Bound: %f\n", bound);
    return (util <= bound);
}

int rm_hyperbolic_bound(taskset_t* taskset){
    float util = 0;
    for(int i = 0; i < taskset->length; i++){
        util *= ((float) taskset->tasks[i]->execution_time / taskset->tasks[i]->period + 1);
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
    if (!rm_least_upper_bound(taskset)) {
        return NULL;
    }

    return NULL;
}