#include <stdio.h>
#include "tasks.h"

int main(int argc, char** argv){
    taskset_t* set = taskset_init();
    printf("Task set initialized.\n");
    taskset_destroy(set);
    printf("Task set destroyed.\n");
    return 0;
}