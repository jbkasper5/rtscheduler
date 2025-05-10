# rtscheduler

This project implements a RISCV bootloader that creates a real-time scheduling process and a task managing process. The scheduling process is responsible for constructing an offline schedule using **Rate Monotonic** and **Earliest Deadline First** algorithms. 

## The LinkerScript

Since this project is trying to boot an empty board, there is no operating system to define system calls, page tables, or any allocation of memory for our program. With that in mind, we need to explicitly define sections of memory such that the bootloader can behave in a predictable manner. To this end, we need to carefully construct the hart's user stacks, trap stacks, and a heap for dynamic memory allocation. 

In this project, each user stack is an 8 KiB stack, the mstacks are all 4 KiB, and the heap is 32 KiB. With this in mind, we have a total of 80 KiB designated for stacks and the heap, reflected in `linker.ld` by defining the `stack_and_heap` section to be `81920` bytes long. 

Alongside the stack and heap sections, we want to create a specific zone designed for inter-hart communication (IHC), which allows the harts to send more than just interrupts to each other. In this system, the hart can trigger a SWI for another hart by writing to the hart's pending interrupt CSR (`sip`), and the revived hart can then read data from it's designated IHC zone that the original sender of the interrupt passed data to. In this fashion, the scheduler hart is able to communicate which tasks should be executing when by passing along this information to the task manager's IHC zone. Much like how the stack and heap sections of memory were defined manually in the linker, the IHC zone must also be manually defined. 

## The Bootloader

This bootloader is implemented using C and RISCV architecture, emulated using QEMU. In general, the boot process is responsible for initializing necessary hardware, constructing the memory spaces, and designating processes to these resources. In this project specifically, the bootloader was responsible for interrupt enabling as well as creating stack memory and spinlocks for process synchronization. This bootloader designates a 4KiB stack, with plans to designate a heap and a custom slab allocator malloc implementation. 

### Interrupts

In order to handle interrupts within the booting process, it's important to understand some of the components of the hardware. In particular, there are a few important **CSRs** (control and status registers) used in creating the bootloader:
+ `mtime`
    + This is the register that contains the current time for the system. This register can be read from address `0x0x200bff8` as per the hardware specifications.
+ `mtimecmp`
    + This is the register that is responsible for triggering timer interrupts. In particular, each hart gets its own `mtimecmp` register for tailored timer interrupts. The `mtimecmp` register for hart 0 begins at address `0x2004000`, and increments by 4 for each subsequent hart. In order to trigger the timer interrupt, you need to add a designated value (representing the amount of time in between timer interrupts) to the value in `mtime` and store it in `mtimecmp`. Once the value in `mtimecmp` is greater than `mtime`, an interrupt is triggered. 
+ `mhartid`
    + This is the register that contains the hart ID for the current executing process. For all intents and purposes, the hart ID in this project corresponds to the core number that the process is executing on. In particular, the scheduler process was designated to run on core 0, and the task managing process was designated to run on core 1. All other cores were trapped and unused. 
+ `mie`
    + This is the register that controls interrupt behavior in machine mode for the current executing hart (hence **m**achine **i**nterrupt **e**nabler). This is a 64-bit value in which the bits correspond to interrupt permissions for the process. In particular, two different configurations were used in this project:
        + `0xA0`: setting `mie` to this value will enable timer interrupts for the current process. Specifically, this sets the MTIE and STIE bits within the `mie` register (corresponding to machine timer interrupt enable and supervisor timer interrupt enable, respectively). This does not allow software interrupts for the current process, and is used by the scheduler
        + `0xF`: setting `mie` to this value will enable all software interrupts, namely MSIE, HSIE, SSIE, and USIE. This does not enable timer interrupts for the current process, and is used by the task manager.
+ `msip`
    + This CSR is responsible for pending software interrupts for a process. In writing to a hart's msip, it will trigger a software interrupt for that process. The `msip` CSR starts at address `0x02000000` for hart 0, and increments by 4 for each hart. In particular, the only process receiving the `msip` CSR is the task manager on hart 1, hence the address `0x02000004` is written to.  
+ `mstatus`
    + Thing

To see more information on the registers and their bitmaps, see [here](https://people.eecs.berkeley.edu/~krste/papers/riscv-privileged-v1.9.1.pdf) for the documentation.

## The Scheduler

### RISC-V QEMU Boards

[here](https://www.qemu.org/docs/master/system/target-riscv.html)