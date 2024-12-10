.section .data
.align 3
printlock: .dword 1

.section .text
.globl lock_acquire
.globl lock_release
.globl wait_for_interrupt

lock_acquire:
    addi sp,sp,-24
    sd ra,0(sp)
    sd s0, 8(sp)
    sd s1, 16(sp)
    la s0, printlock                    # load address of the spinlock

_lock_acquire_loop:
    li t0, 0
    amoswap.w s1, t0, (s0)              # atomic swap with the spinlock, place in zero and read to s1

    beqz s1, _lock_acquire_loop         # if the value returned from the swap was 0, it was already locked
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
    amoswap.w t2, t1, (t0)              # atomically swap a 1 into the spinlock value

    ld ra,0(sp)
    add sp,sp,8
    ret


wait_for_interrupt:
    add sp, sp, -8
    sd ra, 0(sp)
    wfi
    ld ra, 0(sp)
    add sp, sp, 8
    ret
