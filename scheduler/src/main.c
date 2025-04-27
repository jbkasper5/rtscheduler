#include "scheduler.h"
#include "print.h"
#include <stdarg.h>

void test(int nargs, ...);

void test(int nargs, ...){
    va_list list;
    va_start(list, nargs);
    int sum = 0;
    for (int i = 0; i < nargs; i++) {
        sum += va_arg(list, int); // Access arguments
    }
    va_end(list);
    printf("Sum is: %d\n", sum);
    return;
}

int main(int argc, char** argv){
    scheduler();
    return 0;
}