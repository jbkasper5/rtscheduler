.section .data
    .fill 1024, 4, 0
mstack:

.section .text
.globl trap_handler


trap_handler: 
    # since this is a vectored trap handler, we need to multiply the cause by 4
    # to get the trap index

    csrw mscratch, sp               # store user stack into machine scratch
    la  sp, mstack                  # load the machine stack into sp
    addi sp, sp, -24                # normal stack shifting operations, but on machine stack this time
    sd  s0, 0(sp)
    sd  s1, 8(sp)
    sd  s2, 16(sp)

    # TODO: Understand this
    csrr s0, mepc                   # read mepc into s0
    addi s0, s0, 4                  # increment mepc by 4
    csrw mepc, s0                   # write back to mepc 

    csrr s2, mhartid                # load core ID into s2

    li s0, 0
    beq s0, s2, scheduler_trap_handler  # set up trap handler for the scheduler - timer interrupt
    li s0, 1
    beq s0, s2, taskmanager_trap_handler    # set up trap handler for taskmanager - swi

trap_handler_end:
    ld  s0, 0(sp)
    ld  s1, 8(sp)
    ld  s2, 16(sp)
    addi sp, sp, 24
    csrr sp, mscratch               # load the current stack back from machine scratch
    mret                            # return to user space

# set up the trap handler for the scheduler
# should only be on a clock interrupt
scheduler_trap_handler:

    # load the mtime register address
    li t0,0x200bff8

    # load the value from mtime
    lw t0,(t0)
    li t1,50       # change back to 100
    li t2,2047

    # t2 = 204,700
    mul t2,t2,t1

    # increment the value of mtime by t2
    add t0,t0,t2

    # load the mtimecmp address for core 0
    li t1,0x2004000

    # store our maths into the mtimecmp address
    sw t0,(t1) 

    j trap_handler_end

# set up the trap handler for the taskmanager
# should be a software interrupt triggered by the scheduler
taskmanager_trap_handler:

    # acknowledge the interrupt and set the bit back to 0
    li t0, 0x02000004         # address of core 1's msip CSR
    li t1, 0
    sw t1, (t0)
    j trap_handler_end

