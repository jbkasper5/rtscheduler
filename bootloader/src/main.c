#include "main.h"

int main(){
    prints("Test\n");
    while(1){
        prints("Hello from main!\n");
        wait_for_interrupt();
    }
    return 0;
}