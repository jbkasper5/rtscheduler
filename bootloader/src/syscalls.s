.section .text

.globl hartid

hartid:
    addi sp, sp, -8
    sd ra, 0(sp)
    csrr a0, mhartid
    ld ra, 0(sp)
    addi sp, sp, 8
    ret