// #include <stdio.h>
// #include <stdbool.h>
// #include "double_hashing.h"

// #define TABLE_SIZE 256

// void basic_tests() {
//     Table* table = init_table();

//     // Test insertion and search
//     insert(&table, 10);
//     insert(&table, 20);
//     insert(&table, 30);

//     printf("Search 10: %s\n", search(table, 10) ? "Found" : "Not Found");
//     printf("Search 20: %s\n", search(table, 20) ? "Found" : "Not Found");
//     printf("Search 30: %s\n", search(table, 30) ? "Found" : "Not Found");
//     printf("Search 40: %s\n", search(table, 40) ? "Found" : "Not Found"); // Not present

//     // Test deletion
//     remove_key(table, 20);
//     printf("Search 20 after removal: %s\n", search(table, 20) ? "Found" : "Not Found");

//     erase_table(table);
// }

// void duplicate_tests() {
//     Table* table = init_table();

//     insert(&table, 50);
//     insert(&table, 50); // Duplicate
//     insert(&table, 50);

//     int count = search(table, 50) ? 1 : 0;
//     printf("50 exists after duplicate inserts: %d\n", count);

//     remove_key(table, 50);
//     printf("50 exists after removal: %s\n", search(table, 50) ? "Found" : "Not Found");

//     erase_table(table);
// }

// void collision_tests() {
//     Table* table = init_table();

//     // Choose numbers that hash to same index (depends on your hash function)
//     int nums[] = {10, 10 + 10*TABLE_SIZE, 10 + 2*TABLE_SIZE};
//     for (int i = 0; i < 3; i++) {
//         insert(&table, nums[i]);
//     }

//     for (int i = 0; i < 3; i++) {
//         printf("Search %d: %s\n", nums[i], search(table, nums[i]) ? "Found" : "Not Found");
//     }

//     erase_table(table);
// }

// #include <time.h>

// void stress_test(int N) {
//     Table* table = init_table();

//     clock_t start = clock();
//     for (int i = 0; i < N; i++) {
//         insert(&table, i);
//     }
//     clock_t end = clock();

//     printf("Inserted %d elements in %.3f seconds\n", N, (double)(end - start) / CLOCKS_PER_SEC);

//     // Random search test
//     printf("Search %d: %s\n", N/2, search(table, N/2) ? "Found" : "Not Found");
//     printf("Search %d: %s\n", N+1, search(table, N+1) ? "Found" : "Not Found");

//     erase_table(table);
// }

// void edge_case_tests() {
//     Table* table = init_table();

//     // Negative numbers
//     insert(&table, -10);
//     insert(&table, -20);
//     printf("Search -10: %s\n", search(table, -10) ? "Found" : "Not Found");

//     // Zero
//     insert(&table, 0);
//     printf("Search 0: %s\n", search(table, 0) ? "Found" : "Not Found");

//     // Remove non-existent key
//     remove_key(table, 999);
//     printf("Search 999 (never added): %s\n", search(table, 999) ? "Found" : "Not Found");

//     erase_table(table);
// }

// int main() {
//     printf("=== Basic Tests ===\n");
//     basic_tests();

//     printf("\n=== Duplicate Tests ===\n");
//     duplicate_tests();

//     printf("\n=== Collision Tests ===\n");
//     collision_tests();

//     printf("\n=== Edge Case Tests ===\n");
//     edge_case_tests();

//     printf("\n=== Stress Test ===\n");
//     stress_test(50000); // 50k inserts, can adjust

//     return 0;
// }

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "double_hashing.h"

#define BENCHMARK_SIZES 5
#define ITERATIONS 10

typedef struct {
    int size;
    double insert_time;
    double search_time;
    double remove_time;
} BenchmarkResult;

double get_time_ms() {
    return (double)clock() / CLOCKS_PER_SEC * 1000.0;
}

BenchmarkResult benchmark_operations(int size) {
    BenchmarkResult result = {size, 0, 0, 0};
    int* nums = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        nums[i] = rand() % (size * 10);
    }
    
    double start, end;
    
    // Benchmark insert
    start = get_time_ms();
    for (int iter = 0; iter < ITERATIONS; iter++) {
        Table* table = init_table();
        for (int i = 0; i < size; i++) {
            insert(&table, nums[i]);
        }
        erase_table(table);
    }
    end = get_time_ms();
    result.insert_time = (end - start) / ITERATIONS;
    
    // Benchmark search
    Table* table = init_table();
    for (int i = 0; i < size; i++) {
        insert(&table, nums[i]);
    }
    start = get_time_ms();
    for (int iter = 0; iter < ITERATIONS; iter++) {
        for (int i = 0; i < size; i++) {
            search(table, nums[i]);
        }
    }
    end = get_time_ms();
    result.search_time = (end - start) / ITERATIONS;
    
    // Benchmark remove
    start = get_time_ms();
    for (int iter = 0; iter < ITERATIONS; iter++) {
        Table* t = init_table();
        for (int i = 0; i < size; i++) {
            insert(&t, nums[i]);
        }
        for (int i = 0; i < size; i++) {
            remove_key(t, nums[i]);
        }
        erase_table(t);
    }
    end = get_time_ms();
    result.remove_time = (end - start) / ITERATIONS;
    
    erase_table(table);
    free(nums);
    return result;
}

int main() {
    int sizes[] = {100, 500, 1000, 5000, 10000};
    
    printf("Double Hashing Benchmark Results\n");
    printf("==================================================\n");
    printf("%-10s %-15s %-15s %-15s\n", "Size", "Insert (ms)", "Search (ms)", "Remove (ms)");
    printf("==================================================\n");
    
    for (int i = 0; i < BENCHMARK_SIZES; i++) {
        BenchmarkResult res = benchmark_operations(sizes[i]);
        printf("%-10d %-15.4f %-15.4f %-15.4f\n", res.size, res.insert_time, res.search_time, res.remove_time);
    }
    
    printf("==================================================\n");
    printf("(Each operation averaged over %d iterations)\n", ITERATIONS);
    
    return 0;
}