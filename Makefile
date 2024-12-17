SRC_DIR=src
BIN_DIR=bin
BOOTCSRCS=$(shell find bootloader/$(SRC_DIR)/*.c)
BOOTASMSRCS=$(shell find bootloader/$(SRC_DIR)/*.s)
SCHEDCSRCS=$(shell find scheduler/$(SRC_DIR)/*.c)
SRCS:=$(SCHEDCSRCS) $(BOOTCSRCS) $(BOOTASMSRCS)
TOBJS=$(patsubst %.c, %.o, $(SRCS))
TOBJS:=$(patsubst %.s, %.o, $(TOBJS))
TOBJS:=$(patsubst bootloader/$(SRC_DIR)/%, $(BIN_DIR)/%, $(TOBJS))
OBJS=$(patsubst scheduler/$(SRC_DIR)/%, $(BIN_DIR)/%, $(TOBJS))
INCLUDE_PATH=bootloader/include/ -I scheduler/include/
LINKERFILE=bootloader/linker.ld

CC=				riscv64-unknown-elf-gcc
LINKER=			riscv64-unknown-elf-ld
OPT=			-O3
RISCVFLAGS=		-mcmodel=medany -march=rv64g
CFLAGS=			-g -std=c11 -nostdlib -nodefaultlibs -nostartfiles $(RISCVFLAGS)
TARGET=			exe
LFLAGS=			 

all: $(BIN_DIR) $(TARGET)

re: clean all

.PHONY: debug
debug: $(DEBUG_BIN_DIR) $(DTARGET)

# @ is the rule, ^ is the prereqs
$(TARGET): $(OBJS)
	@echo "Hello1"
	$(LINKER) -o $@ $^ -T $(LINKERFILE) $(LFLAGS)

$(BIN_DIR)/%.o: */$(SRC_DIR)/%.c
	@echo "Hello2"
	$(CC) -c $< -o $@ $(RISCVFLAGS) -I $(INCLUDE_PATH) -w

$(BIN_DIR)/%.o: */$(SRC_DIR)/%.s
	@echo "Hello3"
	$(CC) $(RISCVFLAGS) -o $@ -c $< -I $(INCLUDE_PATH)

$(BIN_DIR):
	@echo "Hello4"
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
