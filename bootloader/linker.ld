MEMORY {
  LIM (rwx) : ORIGIN = 0x80000000, LENGTH = 65536
}

SECTIONS {
  .text : {
    bin/boot.o(.text)
    bin/main.o(.text)
    bin/print.o(.text)
    bin/taskmanager.o(.text)
    bin/concurrency.o(.text)
    bin/traphandler.o(.text)
    bin/ipc.o(.text)
  } > LIM
}
