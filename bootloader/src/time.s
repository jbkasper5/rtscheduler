.section .text
.globl time

time:
    addi sp, sp, -16
    sd s0, 8(sp)
    sd ra, 0(sp)

    # load address of mtime
    li s0,0x200bff8

    # load the value from mtime into the return register
    ld a0,(s0)

    ld s0, 8(sp)
    ld ra, 0(sp)
    addi sp, sp, 16
    ret
