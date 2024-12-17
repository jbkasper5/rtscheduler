#include "blmain.h"

unsigned long start = 0;
unsigned long diff = 0;
unsigned long prev = 0;
unsigned long temp = 0;
// int main(){
//     int num_clocks = 1;
//     start = mstime();
//     while(1){
//         prints("Hello from main: ");
//         printi(num_clocks);
//         if(num_clocks % 3 == 0){
//             prints("Start: ");
//             printl(start);
//             temp = mstime();
//             diff = temp - ((diff) ? prev : start);
//             prev = temp;
//             prints("Diff: ");
//             printl(diff);
//             taskmanager_checkup();
//         }
//         wait_for_interrupt();
//         num_clocks++;
//     }
//     return 0;
// }

void taskmanager_checkup(){
    prints("Checking on task manager...\n");
    ping_taskmanager();
}