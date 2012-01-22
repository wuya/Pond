/* *
 *
 *  Copyright © 2012 Isaac    -   kezl -at- bk.ru 
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <limits.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>

#include "chord.h"

#if 0
int distance(t_ident a, t_ident b)
{
    int d = 0;
    if (a == b) {
        return 0;
    } else if (a < b) {
        return b - a; 
    } else {
        return ( ((int) pow(2, M)) + (b - a));
    }
}
#endif

int distance(t_ident a, t_ident b)
{
    /* XOR is good because it is symmetric -
     * distance(a, b) == distance(b, a) */
    return a ^ b;
}


t_cnode *kz_create_ring(t_cnode *start) /* probably a good idea to write
                                           destroy_ring too */
{
    /*
    t_cnode *rt = 0;

    assert(start != 0);
   
    rt = malloc(sizeof(*rt));
    rt->prev = 0;
    rt->next = start;
*/
    start->prev = 0;
    start->next = start;

    return start;
}

void kz_join(t_cnode *start, t_cnode *new_nd)
{
    assert(start != 0);    
    assert(new_nd != 0);
    
    new_nd->prev = 0;
    new_nd->next = kz_find_next(start, new_nd->id);
}

void kz_store(t_cnode *start, t_ident key, t_data value)
{
    t_cnode *s = 0;

    s = kz_find_next(start, key);
    assert(s != 0);
    s->data = value;
}

t_data kz_lookup(t_cnode *start, t_ident key)
{
    t_cnode *l = 0;
    l = kz_find_next(start, key);
    DBG_CNODE_PRINT(l, "lookup");
    
    if (l != 0) {
        /* TODO: do a hash table lookup */
        return l->data;
    }
    return -1;
}

t_ident kz_mkid()
{
    /* TODO: this should return an id generated with SHA-1 */
    /* return RAND_IN_RANGE(0, pow(2, M)); */

    static int i = 0;
    
    ++i;

    return i;
}

t_cnode *kz_find_next(t_cnode *start, t_ident new_id)
{
    /*assert(start->next != 0);*/
    /* TODO: this is the slow version of the algorithm without
       finger tables - when it works, add in the tables */

    /* TODO: add in networking code for the lookup */
#if 0
    if (new_id > start->id && new_id <= start->next->id) { 
        return start->next;
    } else {
        return kz_find_next(start->next, new_id); 
    }
#endif

    t_cnode *cur = 0;

    cur = start;

    while (distance(cur->id, new_id) > distance(cur->next->id, new_id)) {
        DBG_CNODE_PRINT(cur, "cur");
        cur = cur->next;
        DBG_CNODE_PRINT(cur, "cur->next");
    }
    return cur;
}

void kz_cnode_init(t_cnode *cn)
{
    assert(cn != 0);
    cn->data = 0;
    cn->prev = 0;
    cn->next = 0;
    cn->id   = kz_mkid();
}

