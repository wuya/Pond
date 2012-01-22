/* *
 *
 *  Copyright © 2012 Isaac    -   kezl -at- bk.ru 
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef POND_HASH_H 
#define POND_HASH_H

#include <stdlib.h>

struct t_htab_node {
    void                *key;
    void                *data;
    struct t_htab_node  *next;
};

struct t_htab {
    struct t_htab_node **table; 
    size_t size;
    
    int (*compare_fn)(const void *, const void *);
    unsigned int (*hash_fn)(const void *);
};

typedef struct t_htab_node t_htab_node;
typedef struct t_htab t_htab;

t_htab *htab_create(size_t);
unsigned int htab_hash_int(const void *);
unsigned int htab_hash_str(const void *);
int htab_compare_int(const void *, const void *);
int htab_compare_str(const void *, const void *);
int htab_insert(t_htab *, const void *, size_t, const void *, size_t);
t_htab_node *htab_find(const t_htab *, const void *);
void htab_remove_node(t_htab_node **, int *);
int htab_remove(t_htab *, int *);
void htab_destroy(t_htab *);

#endif

