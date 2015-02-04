typedef struct entry {
    char *key;
    char *value;
    struct entry *next;
} entry;

typedef struct hashtable {
    size_t size;
    entry **table;
} hash_table;

extern hash_table *init_hashtable(unsigned long size);
extern unsigned int ht_hash_key(hash_table *ht, char *key);
extern entry *get_entry(hash_table *ht, char *key);
extern char *ht_get(hash_table *ht, char *key);
extern void ht_add(hash_table *ht, char *key, char *value);
