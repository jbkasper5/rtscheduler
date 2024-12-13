#include "main.h"

int main(){
    int num_clocks = 1;
    while(1){
        prints("Hello from main: ");
        printh(num_clocks);
        if(num_clocks % 3 == 0){
            taskmanager_checkup();
        }
        wait_for_interrupt();
        num_clocks++;
    }
    return 0;
}

void taskmanager_checkup(){
    prints("Checking on task manager...\n");
    ping_taskmanager();
}
