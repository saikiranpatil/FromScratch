/**
 * CLOSED HASHING
 * simple implementation of 
 * quadratic probing
 * (causes secondary clustering)
 */
#include<stdlib.h>
#include<assert.h>
#include<stddef.h>

#define INITIAL_TABLE_SIZE 256
#define LOAD_FACTOR 0.75

typedef enum {
    EMPTY,
    PRESENT,
    DELETED
} State;

typedef struct Table {
    size_t capacity;
    size_t size;
    State* states;
    int* keys;
} Table;

Table* create_table(size_t capacity) {
    Table* t = malloc(sizeof(Table));

    assert(t != NULL);

    t->capacity=capacity;
    t->size=0;
    t->states = malloc(capacity * sizeof(State));
    t->keys = calloc(capacity, sizeof(int));
    
    assert(t ->keys != NULL);
    assert(t->states != NULL);
    
    for(size_t i=0;i<capacity;i++) t->states[i]=EMPTY;
    return t;
}

Table* init_table() {
    return create_table(INITIAL_TABLE_SIZE);
}

size_t hash(Table* t, int num) {
    size_t capacity = t->capacity;
    return (num%capacity+capacity)%capacity;
}

void erase_table(Table* t) {
    free(t->states);
    free(t->keys);
    free(t);
}

void insert(Table** tp, int num);
int count(Table* t, int num);

void rehash(Table** tp) {
    Table* t = *tp;
    size_t capacity = t->capacity;
    Table* new_table = create_table(2*capacity);

    for(size_t i=0;i<capacity;i++) {
        if(t->states[i]!=PRESENT) continue;

        insert(&new_table, t->keys[i]);
    }

    erase_table(t);
    *tp=new_table;
}

void insert(Table** tp, int num) {
    Table* t = *tp;

    if(count(t, num)) return;
    
    if((float)t->size/t->capacity>=LOAD_FACTOR) {
        rehash(tp);
        t=*tp;
    }

    int* keys = t->keys;
    State* states = t->states;
    size_t capacity = t->capacity;
    size_t idx = hash(t, num);
    size_t cnt = 0;

    size_t first_deleted = capacity;

    while(states[idx]!=EMPTY) {
        if (states[idx] == DELETED && first_deleted == capacity) {
            first_deleted = idx;
        }
        idx=(idx+1)%capacity;

        // this should not happen if rehashing is correctly implemented
        assert(cnt++<capacity);
    }

    if (first_deleted != capacity) {
        idx = first_deleted;
    }
    
    states[idx]=PRESENT;
    keys[idx]=num;
    t->size++;
}

int count(Table* t, int num) {
    int* keys = t->keys;
    State* states = t->states;
    size_t capacity = t->capacity;
    size_t idx = hash(t, num);
    size_t cnt = 0;

    while(states[idx]!=EMPTY) {
        if(states[idx] == PRESENT && keys[idx] == num) return 1;
        idx=(idx+1)%capacity;

        // this should not happen if rehashing is correctly implemented
        assert(cnt++<capacity);
    }

    return 0;
}


void erase(Table* t, int num) {
    int* keys = t->keys;
    State* states = t->states;
    size_t capacity = t->capacity;
    size_t idx = hash(t, num);
    size_t cnt = 0;

    while(states[idx]!=EMPTY) {
        if(states[idx] == PRESENT && keys[idx] == num) {
            states[idx]=DELETED;
            return;
        }

        idx=(idx+1)%capacity;

        // this should not happen if rehashing is correctly implemented
        assert(cnt++<capacity);
    }
}

int main() {
    return 0;
}