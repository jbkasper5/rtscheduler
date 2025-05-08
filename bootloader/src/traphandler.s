.section .text
.globl trap_handler
.globl taskmanager_trap_handler
.globl scheduler_trap_handler
.globl exit

.altmacro
.macro save_gp i
    addi sp, sp, -8             # make space on stack
  	sd	x\i, 0(sp)              # store register x_i
.endm

.macro load_gp i  
 	ld	x\i, 0(sp)              # load value on stack
    addi sp, sp, 8              # shrink stack
.endm

trap_handler: 
    # store the current t0 into scratch
    csrw mscratch, t0

    # read the hartid into t0
    csrr t0, mhartid

    beq zero, t0, hart0_mstack_init

    addi t0, t0, -1

    beq zero, t0, hart1_mstack_init

    addi t0, t0, -1

    beq zero, t0, hart2_mstack_init

    addi t0, t0, -1

    beq zero, t0, hart3_mstack_init

    mret

hart0_mstack_init:
    la t0, mstackhart0
    j trap_handler_merge

hart1_mstack_init:
    la t0, mstackhart1
    j trap_handler_merge

hart2_mstack_init:
    la t0, mstackhart2
    j trap_handler_merge

hart3_mstack_init:
    la t0, mstackhart3
    j trap_handler_merge

# jump here once the stack has been set up
trap_handler_merge:
    # make room to push user-mode sp onto machine stack
    addi t0, t0, -8

    # store user stack address onto machine stack
    sd sp, 0(t0)

    # move machine stack into sp
    mv sp, t0

    # read t0 back from scratch memory
    csrr t0, mscratch

    # save all registers into the trap stack
    .set 	i, 1
    .rept	31
        save_gp	%i
        .set	i, i+1
    .endr

    # load hart number, cause, and mepc into parameter registers
    csrr a0, mhartid
    csrr a1, mcause
    csrr a2, mepc

    # call the c function for the trap handler
    call traphandler

    # write return value back to mepc
    csrw	mepc, a0

    # restore all registers
    .set 	i, 31
    .rept	31
        load_gp	%i
        .set	i, i-1
    .endr

    # pop the user-mode stack off the trap stack
    ld sp, 0(sp)

    # return to user space via the address from mepc
    mret

# set up the trap handler for the scheduler
# should only be on a clock interrupt
scheduler_trap_handler:
    addi sp, sp, -32
    sd s0, 24(sp)
    sd s1, 16(sp)
    sd s2, 8(sp)
    sd ra, 0(sp)

    # load the mtime register address
    li s0,0x200bff8

    # load the value from mtime
    lw s0,(s0)
    li s1,50       # change back to 100
    li s2,2047

    # t2 = 204,700
    mul s2,s2,s1

    # increment the value of mtime by t2
    add s0,s0,s2

    # load the mtimecmp address for core 0
    li s1,0x2004000

    # store our maths into the mtimecmp address
    sw s0,(s1) 

    ld s0, 24(sp)
    ld s1, 16(sp)
    ld s2, 8(sp)
    ld ra, 0(sp)
    addi sp, sp, 32
    ret

# set up the trap handler for the taskmanager
# should be a software interrupt triggered by the scheduler
taskmanager_trap_handler:
    addi sp, sp, -16
    sd s0, 8(sp)
    sd ra, 0(sp)

    # acknowledge the interrupt and set the bit back to 0
    li s0, 0x02000004         # address of core 1's msip CSR
    sd zero, (s0)

    ld s0, 8(sp)
    ld ra, 0(sp)
    addi sp, sp, 16
    ret


exit:
    li a7, 10
    li a0, 0
    ecall
