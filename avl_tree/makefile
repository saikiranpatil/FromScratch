CC      = gcc
CFLAGS  = -Wall -Wextra -Iinclude
LDFLAGS = -lm

SRC     = src/avl_tree.c src/print_util.c
OBJ     = $(SRC:src/%.c=build/%.o)

BIN_DIR = bin
BLD_DIR = build

all: $(BIN_DIR)/avl

$(BIN_DIR)/avl: $(OBJ) build/main.o | $(BIN_DIR)
	$(CC) $^ $(LDFLAGS) -o $@

build/main.o: src/main.c | $(BLD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: src/%.c | $(BLD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(OBJ)
	$(CC) $(CFLAGS) tests/test_avl.c $^ -o bin/test_avl
	$(CC) $(CFLAGS) tests/test_print.c $^ $(LDFLAGS) -o bin/test_print

$(BIN_DIR) $(BLD_DIR):
	mkdir -p $@

clean:
	rm -rf build bin

.PHONY: all test clean
