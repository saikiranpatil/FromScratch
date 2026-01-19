#include <stdio.h>
#include <stdbool.h>
#include "double_hashing.h"

int main() {
    Table* table = init_table();

    int nums[] = {10, 20, 30, 40, 50, 10};
    for (int i = 0; i < 6; i++) {
        insert(&table, nums[i]);
    }

    printf("Search 30: %s\n", search(table, 30) ? "Found" : "Not Found");
    printf("Search 25: %s\n", search(table, 25) ? "Found" : "Not Found");

    remove_key(table, 30);
    printf("Search 30 after removal: %s\n", search(table, 30) ? "Found" : "Not Found");

    erase_table(table);
    return 0;
}