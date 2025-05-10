.section .text

.globl hartid, set_timer

hartid:
    addi sp, sp, -8
    sd ra, 0(sp)
    csrr a0, mhartid
    ld ra, 0(sp)
    addi sp, sp, 8
    ret

set_timer:
    addi sp, sp, -32
    sd s0, 24(sp)
    sd s1, 16(sp)
    sd s2, 8(sp)
    sd ra, 0(sp)

    # load the mtime register address
    li s0,0x200bff8

    # load the value from mtime
    lw s0,(s0)

    # move the requested time to s2
    move s2, a1

    # increment the value of mtime by s2
    add s0,s0,s2

    # load the mtimecmp address for core 0
    li s1,0x2004000

    # find the correct mtimecmp address for the hart
    slli s2, a0, 3

    # add it to the base mtimecmp
    add s1, s1, s2

    # store the updated time into mtimecmp
    sw s0,(s1) 

    # enable the timer interrupt for the hart
    li s0, 0xaf
    csrs mie, s0  

    # wait until a timer interrupt is triggered
    wfi

    # disable the timer interrupt for the hart (this is for the non-scheduler)
    li s0, 0x0f
    csrs mie, s0  

    ld ra, 0(sp)
    ld s2, 8(sp)
    ld s1, 16(sp)
    ld s0, 24(sp)
    addi sp, sp, 32
    ret


