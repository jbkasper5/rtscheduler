MEMORY {
  LIM (rwx) : ORIGIN = 0x80000000, LENGTH = 131072,
  stack_and_heap (rw) : ORIGIN = 0x80020000, LENGTH = 81920
  other_data (rw) : ORIGIN = 0x80034000, LENGTH = 65536
}

SECTIONS {
  .data : {
    # _start.o defines the stacks and heap segments, so we want it to align first
    bin/_start.o (.data)
  } > stack_and_heap


  .data : {
    # everything else defined in .data can come after the stacks + heap
    bin/*.o (.data)
    bin/*.o (.sdata)
  } > other_data

  .text : {
    # align the start "function" to be the first thing executed
    bin/_start.o (.text)

    # everything else comes after, don't really care about order
    bin/*.o (.text)
  } > LIM
}