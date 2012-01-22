/* *
 *
 *  Copyright © 2012 Isaac    -   kezl -at- bk.ru 
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hash.h"

t_htab
*htab_create(size_t sz)
{
    int i = 0;
    t_htab *h_tbl = 0;
    assert(sz > 1);
    h_tbl = malloc(sizeof(t_htab));
    h_tbl->table = malloc(sz * sizeof(t_htab_node*));
    for (i = 0; i < sz; ++i) {
        h_tbl->table[i] = 0; 
    }
    h_tbl->size = sz;
    return h_tbl;
}

unsigned int
htab_hash_int(const void *key)
{   
    unsigned int a = 0;
    assert(key != 0);
    a = *((int *) key);

    /* Robert Jenkin's 32 bit integer hash */
    a = (a + 0x7ed55d16) + (a << 12);
    a = (a ^ 0xc761c23c) ^ (a >> 19);
    a = (a + 0x165667b1) + (a << 5);
    a = (a + 0xd3a2646c) ^ (a << 9);
    a = (a + 0xfd7046c5) + (a << 3);
    a = (a ^ 0xb55a4f09) ^ (a >> 16);
    return a;
}

unsigned int 
htab_hash_str(const void *key)
{
    /* taken from http://www.cse.yorku.ca/~oz/hash.html */
    const char *k = 0;
    unsigned long h = 5381;
    int c = 0;

    k = (const char*) key;
    
    while ((c = *k++)) {
        h = ((h << 5) + h) + c; /* hash * 33 + c */
    }

    return h;
}

int htab_compare_int(const void *a, const void *b)
{
    return (*((int *) a) == *((int *) b));
}

int htab_compare_str(const void *a, const void *b)
{
    const char *sa = 0, *sb  = 0;

    size_t asz = 0, bsz = 0;
    int ln = 0;

    sa = (const char *) a;
    sb = (const char *) b;

    asz = strlen(sa);
    bsz = strlen(sb);
    
    ln = (asz > bsz) ? bsz : asz;

    return strncmp(sa, sb, ln) == 0;
}

int
htab_insert(t_htab *h_tbl, const void *key, size_t k_sz,
            const void *data, size_t d_sz)
{
    t_htab_node *nt = 0;
    unsigned int h  = 0;

    h = h_tbl->hash_fn(key) % h_tbl->size;
    
    /* do a search to check for duplicates */
    nt = h_tbl->table[h];
    while (nt != 0) {
        if (h_tbl->compare_fn(nt->key, key)) { 
            return -1; /* abort if the key is already found */
        }
        nt = nt->next;
    }
    
    nt       = malloc(sizeof(*nt));
    nt->key  = malloc(k_sz);
    nt->data = malloc(d_sz);
    memcpy(nt->key, key, k_sz);
    memcpy(nt->data, data, d_sz);
    nt->next = h_tbl->table[h];
    h_tbl->table[h] = nt;
    return 0;
}

t_htab_node
*htab_find(const t_htab *h_tbl, const void *key)
{
    unsigned int h = 0;
    t_htab_node *nz = 0;

    h = h_tbl->hash_fn(key) % h_tbl->size;
    
    nz = h_tbl->table[h];
    while (nz != 0) {
        if (h_tbl->compare_fn(nz->key, key)) {
            return nz;
        }
        nz = nz->next;
    }
    return 0;
}

void
htab_remove_node(t_htab_node **n, int *key)
{
    t_htab_node *prv = 0, *cn = 0;

    assert(*n != 0);
    assert(key != 0);

    for (cn = *n; cn != 0; prv = cn, cn = cn->next) {
        if (*((int *) cn->key) == *key) {
            if (prv == 0) {
                *n = cn->next;
            } else {
                prv->next = cn->next;
            }

            free(cn); cn = 0;
            return; /* FIXME: do we need to keep iterating or just return? */
        }
    }
}

int
htab_remove(t_htab *h_tbl, int *key)
{
    unsigned int h = 0;

    assert(h_tbl != 0);
    assert(key != 0);

    t_htab_node *nt = 0;

    h = htab_hash_int(key) % h_tbl->size;

    if (h_tbl->table[h] == 0) {
        return -1;
    }

    nt = h_tbl->table[h];

    htab_remove_node(&(h_tbl->table[h]), key);
    return 0;
}

void
htab_destroy(t_htab *h_tbl)
{
    size_t sz = h_tbl->size;
    unsigned int i = 0;
    
    t_htab_node *cn = 0, *tm = 0;

    /* foreach node */
    for (i = 0; i < sz; ++i) {
        cn = h_tbl->table[i];
        
        /* free the buckets */
        while (cn != 0) {
            tm = cn;
            cn = cn->next;
            free(tm->key); tm->key = 0;
            free(tm->data); tm->data = 0;
            free(tm); tm = 0;
        }
    }
    /* free the table */
    free(h_tbl); h_tbl = 0;
}

