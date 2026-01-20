# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -Isrc

# Source files
SRCS = $(wildcard src/*.c)
LIB_SRCS = $(filter-out src/main.c, $(SRCS))  # all src files except main.c
TEST_SRCS = $(wildcard test/*.c)

# Targets
TARGET = main
TEST_TARGET = run_tests

# Default target
all: $(TARGET)

# Build main program
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

# Build test program (exclude main.c)
$(TEST_TARGET): $(LIB_SRCS) $(TEST_SRCS)
	$(CC) $(CFLAGS) -o $@ $^

# Clean
clean:
	rm -f $(TARGET) $(TEST_TARGET)

# Run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

.PHONY: all clean test
