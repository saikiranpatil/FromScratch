#include <stdio.h>
#include <stdlib.h>
#include "array_utils.h"

int main() {
    int arr1[10] = {1,2,3,4,5,6,7,8,9,0};

    for (int i = 0; i < 10; i++) {
        printf("%d\n", arr1[i]);
    }

    int *arr2 = calloc(10, sizeof *arr2);
    if (!arr2) {
        perror("calloc failed");
        return 1;
    }

    fill_array_index(arr2, 10);

    printf("------------------\n");
    for (int i = 0; i < 10; i++) {
        printf("%d\n", arr2[i]);
    }

    free(arr2);
    return 0;
}
