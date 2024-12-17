#include "schedulebuilders.h"
#include "scheduler.h"

extern void scheduler();

// defines TaskSet
#include "taskset.h"

int main(int argc, char** argv){
    scheduler();
    return 0;
}