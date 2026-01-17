CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11 -g
SRC_DIR := src
TEST_DIR := tests
BUILD_DIR := build

SRC := $(SRC_DIR)/array_utils.c
TEST := $(TEST_DIR)/test_array_utils.c
MAIN := $(SRC_DIR)/main.c

OBJ := $(BUILD_DIR)/array_utils.o
TEST_OBJ := $(BUILD_DIR)/test_array_utils.o
MAIN_OBJ := $(BUILD_DIR)/main.o

APP := $(BUILD_DIR)/app
TEST_BIN := $(BUILD_DIR)/tests

.PHONY: all test run clean

all: $(APP)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(MAIN_OBJ): $(MAIN) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ): $(TEST) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(APP): $(OBJ) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_BIN): $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

test: $(TEST_BIN)
	./$(TEST_BIN)
	@echo "All tests passed ✅"

run: $(APP)
	./$(APP)

clean:
	rm -rf $(BUILD_DIR)
