SRC_DIR=src
BIN_DIR=bin
CSRCS=$(shell find $(SRC_DIR)/*.c)
ASMSRCS=$(shell find $(SRC_DIR)/*.s)
SRCS:=$(CSRCS) $(ASMSRCS)
TOBJS=$(patsubst %.c, %.o, $(SRCS))
TOBJS:=$(patsubst %.s, %.o, $(TOBJS))
OBJS=$(patsubst $(SRC_DIR)/%, $(BIN_DIR)/%, $(TOBJS))
INCLUDE_PATH=include/
LINKERFILE=linker.ld

CC=				riscv64-unknown-elf-gcc
LINKER=			riscv64-unknown-elf-ld
OPT=			-O3
RISCFLAGS=		-mcmodel=medany -march=rv64g
CFLAGS=			-g -std=c11 -nostdlib -nodefaultlibs -nostartfiles $(RISCFLAGS)
TARGET=			exe
LFLAGS=			 

all: $(BIN_DIR) $(TARGET)

re: clean all

.PHONY: debug
debug: $(DEBUG_BIN_DIR) $(DTARGET)

# @ is the rule, ^ is the prereqs
$(TARGET): $(OBJS)
	$(LINKER) -o $@ $^ -T $(LINKERFILE) $(LFLAGS) -DLOCAL

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(RISCFLAGS) -I $(INCLUDE_PATH) -w

$(BIN_DIR)/%.o: $(SRC_DIR)/%.s
	$(CC) $(RISCFLAGS) -o $@ -c $<

$(BIN_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	$(RM) -rf $(TARGET)
	$(RM) -rf $(BIN_DIR)

.PHONY: asm
asm: all
	riscv64-unknown-elf-objdump -d $(TARGET) > asm.s

run: all
	qemu-system-riscv64 -machine sifive_u -serial stdio -bios $(TARGET)

run_wait: all
	qemu-system-riscv64 -machine sifive_u -serial stdio -bios $(TARGET) -S -s 
