SRC_DIR=src
BIN_DIR=bin
DEBUG_BIN_DIR=$(BIN_DIR)/debug
SRCS=$(shell find $(SRC_DIR)/*.c)
TOBJS=$(patsubst %.c, %.o, $(SRCS))
OBJS=$(patsubst $(SRC_DIR)/%, $(BIN_DIR)/%, $(TOBJS))
DOBJS=$(patsubst $(BIN_DIR)/%, $(DEBUG_BIN_DIR)/d_%, $(OBJS))
DEBUG=-DDEBUG
INCLUDE_PATH=include/

CC=				gcc
OPT=			-O3
CFLAGS=			-g -std=c11
TARGET=			exe
DTARGET=		d$(TARGET)

all: $(BIN_DIR) $(TARGET)

re: clean all

.PHONY: debug
debug: $(DEBUG_BIN_DIR) $(DTARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) -I $(INCLUDE_PATH)

$(DTARGET): $(DOBJS)
	$(CC) $^ -o $@ $(CFLAGS) -I $(INCLUDE_PATH)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) -I $(INCLUDE_PATH)

$(DEBUG_BIN_DIR)/d_%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(DEBUG) -I $(INCLUDE_PATH)

$(BIN_DIR) $(DEBUG_BIN_DIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(TARGET)
	rm -rf $(DTARGET)
	rm -rf $(BIN_DIR)
	rm -rf asm.s


.PHONY: asm
asm: all
	objdump -d $(TARGET) > asm.s

.PHONY: valgrind
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)