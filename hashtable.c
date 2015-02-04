#include "hashtable.h"

hash_table *init_hashtable(unsigned long size) {
    if (size < 1) {
        fprintf(stderr, "Invalid Size");
        exit(1);
    }

    hash_table *ht;

    if ((ht = (hash_table *)malloc(sizeof(hash_table))) == NULL)
        return NULL;

    if ((ht->table = (entry **)malloc(sizeof(entry *) * size)) == NULL)
        return NULL;

    size_t x;
    for (x = 0; x < size; x++)
        ht->table[x] = NULL;
    
    ht->size = size;

    return ht;
}

unsigned int ht_hash_key(hash_table *ht, char *key) {
    size_t hash_val = 0;
    size_t i;
    
    for (i = 0; i < strlen(key); i++) {
        hash_val += key[i];
        hash_val += (hash_val << 10);
        hash_val ^= (hash_val >> 6);
    }

    hash_val += (hash_val << 3);
    hash_val += (hash_val >> 11);
    hash_val += (hash_val << 15);
    
    return hash_val % ht->size;
}

entry *get_entry(hash_table *ht, char *key) {
    if (ht->size == 0)
        return NULL;

    unsigned int index = ht_hash_key(ht, key);
    
    entry *curr = ht->table[index];

    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0)
            return curr;
        
        curr = curr->next;
    }

    free(curr);

    return NULL;
}

char *ht_get(hash_table *ht, char *key) {
    entry *e;
    if ((e = get_entry(ht, key)))
        return e->value;
    
    return NULL;
}

void ht_add(hash_table *ht, char *key, char *value) {
    if (ht == NULL || key == NULL || value == NULL)
        return;

    unsigned int index = ht_hash_key(ht, key);
    
    entry *e;
    if ((e = get_entry(ht, key))) {
        free(e->value);
        e->value = value;
        return;
    }

    entry *new_entry = (entry *)malloc(sizeof(entry));
    new_entry->key = key;
    new_entry->value = value;
    new_entry->next = ht->table[index];
    ht->table[index] = new_entry;
}

void json_free(hash_table **json) {
    int i;
    
    for (i = 0; i < 5; i++) {
        int j = 0; 
        for (j = 0; j < 10; j++) {
            free(json[i]->table[j]);
        }

        free(json[i]);
    }

    free(json);
}
