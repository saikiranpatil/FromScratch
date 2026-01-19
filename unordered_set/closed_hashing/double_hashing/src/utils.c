#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

size_t get_max_prime(size_t max_value) {
    if(max_value<2) return 0;

    bool *is_prime=calloc(max_value+1, sizeof(bool));
    if(!is_prime) return 0;

    for(size_t i=2;i<=max_value;i++) is_prime[i]=true;

    for(size_t i=2;i*i<=max_value;i++){
        if (!is_prime[i]) continue;
        for (size_t j=i*i;j<=max_value;j+=i) is_prime[j]=false;
    }
    
    size_t i=max_value;
    while(i-- >= 2){
        if (!is_prime[i]) continue;
        
        free(is_prime);
        return i;
    }

    free(is_prime);
    return 0;
}

size_t hash1(size_t size, int num) {
    return (num%size+size)%size;
}

size_t hash2(size_t size, int num) {
    size_t prime = get_max_prime(size);
    return 1 + num%prime;
}

size_t hash(size_t size, int num, int idx) {
    return (hash1(size, num)+(hash2(size, num)*idx)%size)%size;
}