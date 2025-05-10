#include "taskmanager.h"
#include "scheduler.h"
#include "syscalls.h"

void tm_main(void){
    scheduler_message_t msg;
    while(1){
        // sleep until given directive by the scheduler
        WFI();

        // once the tm is waken, read a communication from the scheduler
        read_message(hartid(), &msg, sizeof(scheduler_message_t));

        // initiate the task given by the scheduler
        task(msg.task, msg.execution_time);

        // clear the old message
        memset(&msg, 0, sizeof(IHC_ZONE_SIZE));
    }
    return;
}


// function to spin a task for it's execution time
void task(int task_num, uint64_t execution_time){
    printf("Starting allotted execution for task %d\n", task_num);

    // subtract 100 to give a small buffer for the TM to finish before being pinged again
    sleep(TIMEUNIT_TO_MS(execution_time) - 100);
    printf("Execution finished.\n");
}