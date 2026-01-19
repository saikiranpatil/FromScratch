CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude -g
SRC = src/main.c src/utils.c src/double_hashing.c
OBJ = $(SRC:.c=.o)
TARGET = hash_test

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)