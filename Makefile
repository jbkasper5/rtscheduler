SRC_DIR=src
BIN_DIR=bin
BOOTCSRCS=$(shell find bootloader/$(SRC_DIR)/*.c 2>/dev/null)
BOOTASMSRCS=$(shell find bootloader/$(SRC_DIR)/*.s 2>/dev/null)
SCHEDCSRCS=$(shell find scheduler/$(SRC_DIR)/*.c 2>/dev/null)
SCHEDASMSRCS=$(shell find scheduler/$(SRC_DIR)/*.s 2>/dev/null)
SRCS:=$(SCHEDCSRCS) $(SCHEDASMSRCS) $(BOOTCSRCS) $(BOOTASMSRCS)
TOBJS=$(patsubst %.c, %.o, $(SRCS))
TOBJS:=$(patsubst %.s, %_s.o, $(TOBJS))
TOBJS:=$(patsubst %_start_s.o, %_start.o, $(TOBJS))
TOBJS:=$(patsubst bootloader/$(SRC_DIR)/%, $(BIN_DIR)/%, $(TOBJS))
OBJS=$(patsubst scheduler/$(SRC_DIR)/%, $(BIN_DIR)/%, $(TOBJS))
INCLUDE_PATH=bootloader/include/ -I scheduler/include/
LINKERFILE=bootloader/linker.ld

CC=				riscv64-unknown-elf-gcc
LINKER=			riscv64-unknown-elf-ld
OPT=			-O3
RISCVFLAGS=		-mcmodel=medany -march=rv64g -mabi=lp64
CFLAGS=			-g -std=c11 -nostdlib -nodefaultlibs -nostartfiles $(RISCVFLAGS)
TARGET=			exe
LFLAGS=			 

all: $(BIN_DIR) $(TARGET)

re: clean all

.PHONY: debug
debug: $(DEBUG_BIN_DIR) $(DTARGET)

# @ is the rule, ^ is the prereqs
$(TARGET): $(OBJS)
	@echo $(OBJS)
	$(LINKER) -o $@ $^ -T $(LINKERFILE) $(LFLAGS)

$(BIN_DIR)/%.o: */$(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(RISCVFLAGS) -I $(INCLUDE_PATH) -w

# append an _s to the assembly object files to allow same-name files
$(BIN_DIR)/%_s.o: */$(SRC_DIR)/%.s
	$(CC) $(RISCVFLAGS) -o $@ -c $< -I $(INCLUDE_PATH)

# unknown ELF requires a start.o object, so we need to compile this specially
$(BIN_DIR)/_start.o: */$(SRC_DIR)/_start.s
	$(CC) $(RISCVFLAGS) -o $@ -c $< -I $(INCLUDE_PATH)

$(BIN_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	$(RM) -rf $(TARGET)
	$(RM) -rf **/$(BIN_DIR)
	$(RM) -rf $(BIN_DIR)
	$(RM) -rf objdump.s
	$(RM) -rf *.txt

.PHONY: asm
asm: all
	riscv64-unknown-elf-objdump -d $(TARGET) > objdump.s

run: all
	qemu-system-riscv64 -machine sifive_u -serial stdio -bios $(TARGET)

elf: all
	riscv64-unknown-elf-readelf -a $(TARGET) > elf.txt

run_wait: all
	qemu-system-riscv64 -machine sifive_u -serial stdio -bios $(TARGET) -S -s 