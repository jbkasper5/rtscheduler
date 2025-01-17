#include "schedulebuilders.h"
#include "print.h"

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
    float X[10] = {x / n, 0, 0, 0, 0, 0, 0, 0, 0, 0};  // X_0 = initial guess
    for (int i = 0; i < 9; i++) {
        X[i + 1] = ((n - 1) * X[i] / n) + ((x / n) * (1 / nth_pow(X[i], n - 1)));
    }
    return X[9];  // hopefully 9 iterations is good enough
}

int rm_least_upper_bound(taskset_t* taskset) {
    float util = 0;
    for (int i = 0; i < taskset->length; i++) {
        util += (float)(taskset->tasks[i]->execution_time / taskset->tasks[i]->period);
    }
    float bound = taskset->length * (nth_root(2, taskset->length) - 1);
    return (util <= bound);
}

int rm_hyperbolic_bound(taskset_t* taskset) {
    float util = 0;
    for (int i = 0; i < taskset->length; i++) {
        util *= ((float)taskset->tasks[i]->execution_time / taskset->tasks[i]->period + 1);
    }
    P("Product: %f\n", util);
    return (util <= 2);
}

int rm_response_time_analysis(taskset_t* taskset) { return 0; }

int edf_utilization_bound(taskset_t* taskset) {
    double u = 0;
    for (int i = 0; i < taskset->length; i++) {
        task_t* task = taskset->tasks[i];
        u += task->execution_time / task->period;
    }
    return u <= 1;
}

void min_period(taskset_t* taskset, task_t* out[], int* indexes) {
    // iterate over all tasks in the taskset
    for (int i = 0; i < taskset->length; i++) {

        // get the minimum task, equal to the current task
        task_t* min = taskset->tasks[i];

        // save the minimum index
        int index = i;

        // iterate over the remaining tasks in the taskset
        for (int j = i + 1; j < taskset->length; j++) {

            // if the task has a period less than that of our minimum, we swap
            if (taskset->tasks[j]->period < min->period) {
                min = taskset->tasks[j];
                index = j;
            }
        }

        // mark index i as task with the minimum period from the remaining tasks
        out[i] = min;

        // if indexes isn't null, set the current task index to index
        if (indexes != NULL) {
            indexes[i] = index;
        }
    }
}

// TODO: make generic
void min_deadline(taskset_t* taskset, task_t* out[], int* indexes) {
    for (int i = 0; i < taskset->length; i++) {
        task_t* min = taskset->tasks[i];
        int index = i;
        for (int j = i + 1; j < taskset->length; j++) {
            if (taskset->tasks[j]->period < min->period) {
                min = taskset->tasks[j];
                index = j;
            }
        }
        out[i] = min;

        if (indexes != NULL) {
            indexes[i] = index;
        }
    }
}

schedule_t* edf_scheduler(taskset_t* taskset) {
    schedule_t* schedule = (schedule_t*) malloc(sizeof(schedule_t));
    pq_t* pq = pq_init(taskset->length);

    pq_destroy(pq);
    return schedule;
}

schedule_t* rm_scheduler(taskset_t* taskset) {
    schedule_t* schedule = (schedule_t*) malloc(sizeof(schedule_t));
    pq_t* pq = pq_init(taskset->length);
    
    pq_destroy(pq);
    return schedule;
}