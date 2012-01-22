/* *
 *
 *  Copyright © 2012 Isaac    -   kezl -at- bk.ru 
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef POND_CHORD_H 
#define POND_CHORD_H 

#define RAND_IN_RANGE(x, y) ((y) - (x)) * (rand() / (RAND_MAX + 1.0)) + (x)

#define M   sizeof(t_ident) * 8 /* m-identifier bits*/

#define DBG_CNODE_PRINT(cn, lbl)\
        do {\
            printf("DBG_CNODE_PRINT for %s\n", (lbl));\
            printf("this: %p\n", (cn));\
            printf("id: %d\n", (int) (cn)->id);\
            printf("data: %d\n", (int) (cn)->data);\
            printf("next: %p\n", (cn)->next);\
            printf("prev: %p\n\n", (cn)->prev);\
        } while (0) 

typedef unsigned long   t_ident; /* TODO: use a big number library for this */
typedef int             t_data;  /* TODO: use a hash table for this */


struct t_cnode {
    t_ident     id;
    t_data      data;

    struct t_cnode       *next;
    struct t_cnode       *prev;
};

typedef struct t_cnode t_cnode;


t_cnode *kz_create_ring(t_cnode *);
void kz_join(t_cnode *, t_cnode *);
void kz_store(t_cnode *, t_ident, t_data);
t_data kz_lookup(t_cnode *, t_ident);
t_ident kz_mkid();
t_cnode *kz_find_next(t_cnode *, t_ident);
void kz_cnode_init(t_cnode *);

#endif /* POND_CHORD_H */

