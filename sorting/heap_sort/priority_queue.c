#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define DEFAULT_SIZE 16

/**
 * Simple implementation
 * of Max Heap
 */

typedef struct PQ {
    int *nums;
    size_t size;
    size_t capacity;
} PQ;

void swap(int *a, int *b) {
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

PQ *create_pq(size_t capacity) {
    PQ *new_pq = malloc(sizeof(PQ));
    assert(new_pq != NULL);

    new_pq->nums = calloc(capacity, sizeof(int));
    assert(new_pq->nums != NULL);

    new_pq->capacity = capacity;
    new_pq->size = 0;

    return new_pq;
}

PQ *resize(PQ *pq) {
    assert(pq!=NULL);

    pq->capacity*=2;
    pq->nums=realloc(pq->nums, pq->capacity * sizeof(int));

    assert(pq->nums!=NULL);

    return pq;
}

void insert(PQ **pq_ptr, int num) {
    PQ *pq=*pq_ptr;

    if (!pq) pq = create_pq(DEFAULT_SIZE);
    if (pq->size == pq->capacity) pq = resize(pq);

    *pq_ptr = pq;

    pq->nums[pq->size] = num;
    int idx = pq->size++;

    // swap the inserted element with its parent if
    // its order is not maintained
    while (idx > 0 && pq->nums[idx] > pq->nums[(idx - 1) / 2])
    {
        swap(&pq->nums[idx], &pq->nums[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}

void pop_max(PQ **pq_ptr) {
    PQ *pq = *pq_ptr;

    if (!pq) return;

    swap(&pq->nums[0], &pq->nums[--pq->size]);

    size_t idx = 0;
    while (1) {
        size_t left = 2 * idx + 1;
        size_t right = 2 * idx + 2;
        size_t curr = idx;

        if (left < pq->size && pq->nums[curr] < pq->nums[left]) curr = left;
        if (right < pq->size && pq->nums[curr] < pq->nums[right]) curr = right;

        if (curr == idx) break;

        swap(&pq->nums[idx], &pq->nums[curr]);
        idx = curr;
    }
}

int peak(PQ *pq) {
    if (!pq || pq->size == 0) return -1;
    return pq->nums[0];
}

void destroy_pq(PQ *pq) {
    if (!pq) return;
    free(pq->nums);
    free(pq);
}

int main() {
    PQ *root = NULL;
    int nums[] = {1, 89, 45, 40, 12};

    for(size_t i=0;i<5;i++) insert(&root, nums[i]);

    // Pop one-by-one elements
    // to get the sorted numbers
    for (size_t i = 0; i < 5; i++) {
        printf("%d ", peak(root));
        pop_max(&root);
    }

    destroy_pq(root);

    return 0;
}