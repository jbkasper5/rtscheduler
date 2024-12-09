#include "main.h"

int main(){
    lock_acquire();
    prints("Hello from main!\n");
    lock_release();
    return 0;
}