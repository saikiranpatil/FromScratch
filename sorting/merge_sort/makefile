CC := gcc
CFLAGS := -I./include

main: src/main.c src/merge_sort.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f main

.PHONY: clean
