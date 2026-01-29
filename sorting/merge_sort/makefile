all:
	gcc -Wall -Wextra -Iinclude src/main.c src/merge_sort.c -o merge_sort

test:
	gcc -Wall -Wextra -Iinclude src/merge_sort.c test/test_merge_sort.c -o test_merge_sort

clean:
	rm -f merge_sort test_merge_sort