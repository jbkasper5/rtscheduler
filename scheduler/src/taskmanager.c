#include "taskmanager.h"
#include "print.h"
#include "time.h"
#include "malloc.h";


void task(unsigned long execution_time);


void tm_main(void){
    long* val;
    while(1){
        WFI();
        val = (long*) malloc(sizeof(long));
        prints("Task checkup number ");
        printl(*val);
        (*val)++;
        free(val);
    }
    return;
}


// function to spin a task for it's execution time
void task(unsigned long execution_time){
    WFI();
}