.extern init

# create 4 stacks, each 8 KiB, one per hart
.section .data
    .fill 2048, 4, 0
hart0stack:
    .fill 2048, 4, 0
hart1stack:
    .fill 2048, 4, 0
hart2stack:
    .fill 2048, 4, 0
hart3stack:
    .fill 1024, 4, 0
mstackhart0:
    .fill 1024, 4, 0
mstackhart1:
    .fill 1024, 4, 0
mstackhart2:
    .fill 1024, 4, 0
mstackhart3:
heap:
    .fill 8192, 4, 0
.globl heap
.globl hart0stack, hart1stack, hart2stack, hart3stack
.globl mstackhart0, mstackhart1, mstackhart2, mstackhart3

.section .text
_start:
    j init
