#include <assert.h>
#include <stdlib.h>
#include "array_utils.h"

void test_fill_array_index() {
    int arr[10];
    fill_array_index(arr, 10);

    for (int i = 0; i < 10; i++) {
        assert(arr[i] == i);
    }
}

void test_calloc_zero_init() {
    int *arr = calloc(10, sizeof *arr);
    assert(arr != NULL);

    for (int i = 0; i < 10; i++) {
        assert(arr[i] == 0);
    }

    free(arr);
}

int main() {
    test_fill_array_index();
    test_calloc_zero_init();

    return 0;
}
