/* Skip Lists: A Probabilistic Alternative to Balanced Trees */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include"myheader.hpp" // It includes the header file in which diffent skiplist functions are implemented.

int main() {
    int arr[] = { 3, 6, 9, 2, 11, 1, 4 }, i;
    skiplist list; // a variable skiplist is defined
    skiplist_init(&list); // skiplist is initialised

    printf("Insert:--------------------\n");
    for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        skiplist_insert(&list, arr[i], arr[i]);
    }
    skiplist_dump(&list); // prints all the elemnts present in skip list

    printf("Search:--------------------\n");
    int keys[] = { 3, 4, 7, 10, 111 };

    for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        snode *x = skiplist_search(&list, keys[i]); // search for a key in skiplist
        if (x) {
            printf("key = %d, value = %d\n", keys[i], x->value);
        } else {
            printf("key = %d, not found\n", keys[i]);
        }
    }

    skiplist_delete(&list, 3); // deletes a key from skiplist
    skiplist_delete(&list, 9);
    skiplist_dump(&list);

    return 0;
}
