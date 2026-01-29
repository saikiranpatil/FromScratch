#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include "merge_sort.h"

void test_sorting() {

    int nums[] = {5, 6, 78, 56, 8, 11, 1};
    size_t n = sizeof(nums) / sizeof(int);
    
    int* tmp = malloc(n*sizeof(int));
    if(!tmp) return;
    
    mergeSort(nums, 0, n-1, tmp);
    
    // 1. nums should not be empty
    assert(nums!=NULL);
    
    // 2. nums are correctly sorted
    int sorted[] = {1, 5, 6, 8, 56, 78};
    for(size_t i=0;i<n;i++) assert(nums[i]==sorted[i]);
    
    free(tmp);
}

int main() {
    test_sorting();

    return 0;
}