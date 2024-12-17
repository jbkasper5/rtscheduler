.section .data
.align 3
printlock: .dword 1

.section .text
.globl wait_for_interrupt


wait_for_interrupt:
    add sp, sp, -8
    sd ra, 0(sp)
    wfi
    ld ra, 0(sp)
    add sp, sp, 8
    ret
