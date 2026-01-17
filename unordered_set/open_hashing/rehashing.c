/**
 * OPEN HASHING
 * simple open-hashing implementation of unordered_set
 * using simple hashing and linked-list 
 * for collusion handling
 */

#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include<assert.h>

#define INITIAL_TABLE_SIZE 256
#define LOAD_FACTOR 0.75

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct Table {
    Node** nums;
    size_t size;
    size_t capacity;
} Table;

Table* create_table(size_t capacity) {
    Table* t=malloc(sizeof(Table));
    
    assert(t!=NULL);


    t->capacity=capacity;
    t->size=0;
    t->nums=calloc(capacity, sizeof(*t->nums));

    if(t->nums==NULL) {
        assert(t->nums!=NULL);
        free(t);
        return NULL;
    }

    return t;
}

Table* init_table() {
    return create_table(INITIAL_TABLE_SIZE);
}

size_t hash(Table* t, int num) {
    size_t capacity = t->capacity;
    return (num%capacity+capacity)%capacity;
}

void insert(Table** ct, int num);

void rehash(Table** ct) {
    Table* t=*ct;
    Table* new_table=create_table(t->capacity*2);
    Node** curr_nums = t->nums;

    for(int i=0;i<t->capacity;i++) {
        Node* curr=curr_nums[i];
        while(curr) {
            insert(&new_table, curr->value);

            Node* next=curr->next;
            free(curr);
            curr=next;
        }
    }

    free(curr_nums);
    free(t);

    *ct=new_table;
}

void insert(Table** ct, int num) {
    Table* t=*ct;
    int hash_value=hash(t, num);
    Node* curr=t->nums[hash_value];
    while(curr) {
        if(curr->value==num) return;
        curr=curr->next;
    }

    if((float)t->size/t->capacity>=LOAD_FACTOR) {
        rehash(&t);
        t=*ct;
    }
    
    hash_value=hash(t, num);
    Node* new_node = malloc(sizeof(Node));
    new_node->value=num;
    new_node->next=t->nums[hash_value];
    t->nums[hash_value]=new_node;
    t->size++;
}

int main() {
    return 0;
}