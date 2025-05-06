#include "scheduler.h"
#include "print.h"
#include <stdarg.h>

extern long heap;
extern long hart0stack, hart1stack, hart2stack, hart3stack;
extern long mstackhart0, mstackhart1, mstackhart2, mstackhart3;
extern long hart0ihczone, hart1ihczone, hart2ihczone, hart3ihczone;

int main(int argc, char** argv){
    printf("Hart 0 stack: 0x%x\n", &hart0stack);
    printf("Hart 1 stack: 0x%x\n", &hart1stack);
    printf("Hart 2 stack: 0x%x\n", &hart2stack);
    printf("Hart 3 stack: 0x%x\n", &hart3stack);

    printf("Hart 0 mstack: 0x%x\n", &mstackhart0);
    printf("Hart 1 mstack: 0x%x\n", &mstackhart1);
    printf("Hart 2 mstack: 0x%x\n", &mstackhart2);
    printf("Hart 3 mstack: 0x%x\n", &mstackhart3);
    
    printf("Heap addr: 0x%x\n", &heap);

    printf("Hart 0 IHC zone: 0x%x\n", &hart0ihczone);
    printf("Hart 1 IHC zone: 0x%x\n", &hart1ihczone);
    printf("Hart 2 IHC zone: 0x%x\n", &hart2ihczone);
    printf("Hart 3 IHC zone: 0x%x\n", &hart3ihczone);
    scheduler();
    return 0;
}