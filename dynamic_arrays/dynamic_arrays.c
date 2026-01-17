#include<stdlib.h>
#include<stdio.h>
#include<assert.h>

typedef struct Darray {
    int *data;
    size_t capacity;
    size_t size;
} Darray;

void initialize(Darray *darray, size_t init_size) {
    darray->data=malloc(init_size * (sizeof *darray->data));

    assert(darray->data!=NULL);

    darray->size=0;
    darray->capacity=init_size;
}

void push_back(Darray *darray, int num) {
    if(darray->size==darray->capacity) {
        darray->data = realloc(darray->data, darray->capacity * 2 * sizeof *darray->data);
        assert(darray->data!=NULL);
        darray->capacity*=2;
    }

    darray->data[darray->size++]=num;
}

int main() {
    Darray *darray;
    initialize(darray, 8);

    for(int i=0;i<10;i++) {
        push_back(darray, i);
    }

    for(int i=0;i<10;i++) {
        printf("%d\n",darray->data[i]);
    }

    return 0;
}