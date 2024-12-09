# create an 8KiB region of memory, initialized to zero
.section .data
    .fill 2048, 4, 0
stack:

printlock: .word 1

.section .text
.globl lock_acquire
.globl lock_release
.globl _start

_start:
    la sp, stack                        # set sp equal to the stack pointer
    la t0, trap_handler                 # set up the machine trap handler jump vector
    csrw mtvec, t0                      # set up jump vector
    csrr t0, mhartid                    # get the core ID using atomic read instruction

    li t1, 0
    bne t0, t1, _skip_scheduler_proc     # if this is not core 0, skip over scheduler initialization
    jal scheduler_proc_init
    j _infinite

_skip_scheduler_proc:
    li t1, 1                            # load 1 into t1
    csrr t0, mhartid                    # get the core ID using atomic read instruction
    bne t0, t1, _infinite               # any core with a value other than 1 gets trapped
    jal taskman_proc_init               # if this is core 1, jump to task manager initialiuation
    j _infinite



trap_handler: 
    mret



scheduler_proc_init:
    add sp,sp,-8
    sd ra,0(sp)
    csrr a0, mhartid                    # get the core ID using atomic read instruction
    jal printi
    jal main                            # jump to main function
    ld ra,0(sp)
    add sp,sp,8
    ret


taskman_proc_init:
    add sp,sp,-8
    sd ra,0(sp)
    csrr a0, mhartid                    # get the core ID using atomic read instruction
    jal printi
    jal taskmain                        # jump to task manager's main function
    ld ra,0(sp)
    add sp,sp,8
    ret


lock_acquire:
    addi sp,sp,-24
    sd ra,0(sp)
    sd s0, 8(sp)
    sd s1, 16(sp)
    # la s0, printlock                   # load address of the spinlock integer
    # move a0, s0
    # jal printi

    # can load and store from s0 just fine
    # li t0, -2
    # sd t0, (s0)
    # ld a0, (s0)
    # jal printi

_lock_acquire_loop:
    # causes segmentation fault
    # amoswap.w s1, zero, (t0)
    lw s1, (s0)
    sw zero, (s0)
    beqz s1, _lock_acquire_loop      # if the value returned from the swap was 0, it was already locked

    ld ra,0(sp)
    ld s0,8(sp)
    ld s1,16(sp)
    addi sp,sp,24
    ret

lock_release:
    add sp,sp,-8
    sd ra,0(sp)

    la t0, printlock                    # load address of spinlock
    li t1, 1                            # load immediate 1, for unlocked
    
    # causes segmentation fault
    # amoswap.w t2, t1, (t0)              # swap the 1 in place
    sw t1, (t0)

    ld ra,0(sp)
    add sp,sp,8
    ret


_infinite:    
#    csrr a0, mhartid                    # get the core ID using atomic read instruction
#    jal printi
    j _infinite

