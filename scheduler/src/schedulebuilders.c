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
    printf("Utilization: %f\n", util);
    printf("Bound: %f\n", bound);
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

schedule_t* edf_scheduler(taskset_t* taskset) { return NULL; }

schedule_t* rm_scheduler(taskset_t* taskset) {
    if (!rm_least_upper_bound(taskset)) {
        return NULL;
    }
    taskset->schedulable = TRUE;

    schedule_t* schedule = malloc(sizeof(schedule_t));

    // Sort tasks by smallest -> largest period
    task_t* minPeriod[taskset->length];
    int indexes[taskset->length];
    for (int i = 0; i < taskset->length; i++) {
        task_t* min = taskset->tasks[i];
        int index = i;
        for (int j = i + 1; j < taskset->length; j++) {
            if (taskset->tasks[j]->period < min->period) {
                min = taskset->tasks[j];
                index = j;
            }
        }
        minPeriod[i] = min;
        indexes[i] = index;
    }

    // assuming execution time < period
    // and no preemption
    // initialize schedule to -1 at all time t
    schedule->schedule = malloc(sizeof(int) * minPeriod[0]->period);
    for (int i = 0; i < minPeriod[0]->period; i++) {
        schedule->schedule[i] = -1;
    }

    // fill in which task is executing at which t based on their period
    // assuming each index in the schedule is 1 time unit away
    int t = 0;
    for (int i = 0; i < taskset->length; i++) {
        task_t* task = minPeriod[i];

        // could fit other tasks based on their offset here
        while (t < (int)(task->offset)) {
            t++;
        }

        for (int j = 0; j < task->execution_time; j++) {
            schedule->schedule[t] = indexes[i];
            t++;
        }
    }

    // for (int i = 0; i < minPeriod[0]->period; i++) {
    //     printf("%d ", schedule->schedule[i]);
    // }
    // printf("\n");

    return schedule;
}