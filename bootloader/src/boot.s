# create an 8KiB region of memory, initialized to zero
.section .data
.align 3
printlock: .dword 1

.section .text
.globl init
.globl _infinite

init:
    # 11 leading zeroes, then 11 -> 0001 1000 0000 0000
    # two ones set both MPP bits to 1
    li      t0, 0x3800                  # address of MIE within mstatus
    csrc    mstatus, t0                 # enable machine-mode interrupts

    # binary -> 1000 0000 1010
    # first nibble sets SIE and MIE, third nibble sets lower bit of MPP
    li      t0, 0x80A                   # address of SIE within mstatus
    csrs    mstatus, t0                 # enable supervisor-mode interrupts

    la t0, trap_handler                 # set up the machine trap handler jump vector
    csrw mtvec, t0                      # set up jump vector

    # build the schedule so all cores can see it
    # jal build_schedule

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


scheduler_proc_init:
    la sp, hart0stack                        # set sp equal to the stack pointer
    addi sp,sp,-8
    sd ra,0(sp)

    # enable timer interrupts only for the scheduling process
    li t0, 0xa0
    csrs mie, t0

    jal main                            # jump to main function
    ld ra,0(sp)
    addi sp,sp,8
    ret


taskman_proc_init:
    la sp, hart1stack                        # set sp equal to the stack pointer
    addi sp,sp,-8
    sd ra,0(sp)

    # enable software interrupts for only the task manager process
    li t0, 0xf
    csrs mie, t0                             

    jal tm_main                        # jump to task manager's main function
    ld ra,0(sp)
    addi sp,sp,8
    ret


_infinite:    
    j _infinite                         # trap other cores