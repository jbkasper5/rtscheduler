.section .text
.globl ping_taskmanager

ping_taskmanager:
    addi sp, sp, -24
    sd s1, 16(sp)
    sd s0, 8(sp)
    sd ra, 0(sp)

    li s0, 0x02000004         # address of core 1's msip CSR

    li s1, 1
    sw s1, (s0)

    ld ra, 0(sp)
    ld s0, 8(sp)
    ld s1, 16(sp)
    addi sp, sp, 24
    ret
    