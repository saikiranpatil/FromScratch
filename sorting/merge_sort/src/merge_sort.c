#include<stdio.h>
#include<stdlib.h>

void merge(int* nums, int l, int m, int r, int* tmp) {
    int i1 = 0, i2 = 0, i = 0;
    int n1 = m-l+1, n2 = r-m;

    while(i1<n1 || i2<n2) {
        if(i1==n1 || (i2<n2 && nums[m+1+i2]<nums[l+i1])) {
            tmp[l+i++]=nums[m+1+i2++];
        } else {
            tmp[l+i++]=nums[l+i1++];
        }
    }

    for(size_t i=l;i<=r;i++) nums[i]=tmp[i];
}

void mergeSort(int* nums, int l, int r, int* tmp) {
    if(l>=r) return;

    int m=l+(r-l)/2;

    mergeSort(nums, l, m, tmp); 
    mergeSort(nums, m+1, r, tmp);

    merge(nums, l, m, r, tmp);
}