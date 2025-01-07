#include "taskmanager.h"
#include "print.h"
#include "time.h"
#include "malloc.h";


void task(unsigned long execution_time);


void tm_main(void){
    long val = 0;
    while(1){
        WFI();
        ++val;
        prints("Task checkup number ");
        printl(val);
    }
    return;
}


// function to spin a task for it's execution time
void task(unsigned long execution_time){
    WFI();
}