#include<stdlib.h>
#include<stdio.h>

void fill_array_index(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

int main() {
    int arr1[10] = {1,2,3,4,5,6,7,8,9,0};
    for(int i=0;i<10;i++) {
        printf("%d\n", arr1[i]);
    }
    
    int *arr2 = calloc(10, sizeof *arr2);

    if(arr2==NULL) {
        perror("Error allocating memory for arr2");
    }

    for(int i=0;i<10;i++) {
        arr2[i]=i;
    }

    printf("------------------\n");

    for(int i=0;i<10;i++) {
        printf("%d\n", arr2[i]);
    }
    
    free(arr2);

    int *arr3 = arr1;

    printf("------------------\n");
    
    for(int i=0;i<10;i++) {
        printf("%d\n", arr3[i]);
    }

    return 0;
}