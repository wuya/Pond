/* *
 *
 *  Copyright © 2012 Isaac    -   kezl -at- bk.ru 
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "chord.h"

#if 0
    /* demonstration of how to use the hash table */
    int a = 2, b = 3, c = 4, d = 5;

    t_htab  *myhtab = 0;
    t_htab_node *nt = 0;

    myhtab = htab_create(32);

    myhtab->hash_fn = htab_hash_int;
    myhtab->compare_fn = htab_compare_int;

    htab_insert(myhtab, &a, sizeof(a), &b, sizeof(b));
    htab_insert(myhtab, &c, sizeof(c), &d, sizeof(d));

    nt = htab_find(myhtab, &a);
    printf("a -> %d\n", *((int *) nt->data));

    nt = htab_find(myhtab, &c);
    printf("b -> %d\n", *((int *) nt->data));

    htab_remove(myhtab, &c);
    nt = htab_find(myhtab, &c);
    if (nt == 0) {
        printf("successfully removed\n");
    }

    htab_destroy(myhtab);
#endif

int main(void)
{
    srand(time(0));

#if 1
    t_cnode *root = 0;
    t_cnode start, follower, another;

    t_data key = 0, value = 0;
    
    kz_cnode_init(&start);
    kz_cnode_init(&follower);
    kz_cnode_init(&another);
	root = &start;
    kz_join(&follower,&start);
	kz_join(&start,&another);
 //   root->next = &another; /* FIXME: should not have to 'manually' do this... */

    DBG_CNODE_PRINT(root, "root");
    DBG_CNODE_PRINT(&follower, "follower");
    DBG_CNODE_PRINT(&another, "another"); 
    key = kz_mkid(); /* key is just some arbitrary hash, so just make
                        it another id for now */
#endif

#if 0
    /* this is only relevant when there is a hashtable in the structure */
    value = kz_lookup(root, key);
    printf("got back: %d\n", value);
    if (value == -1) {
        kz_store(root, key, value);
        printf("stored:\nkey: %d, value: %d at %p\n", key, value, root);
    }

    value = kz_lookup(root, key);
    printf("value: %d\n", value);
#endif
   // getchar();
    return 0;
}

