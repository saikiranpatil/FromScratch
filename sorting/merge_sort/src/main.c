#include<stdlib.h>
#include<stdio.h>
#include "merge_sort.h"

int main() {
    int nums[] = {5, 6, 78, 56, 8, 11, 1};
    int n = sizeof(nums) / sizeof(int);
    
    int* tmp = malloc(n*sizeof(int));
    if(!tmp) return -1;
    
    mergeSort(nums, 0, n-1, tmp);
    
    for(size_t i=0;i<n;i++) printf("%d, ", nums[i]);

    free(tmp);
    return 0;
}