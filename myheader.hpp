#ifndef myheader
#define SKIPLIST_MAX_LEVEL 6 // Maximum capacity of skip list is currently set to 6, change if desired

// structures defined for skip list implementation
typedef struct snode {
    int key;
    int value;
    struct snode **forward;
} snode;

typedef struct skiplist {
    int level;
    int size;
    struct snode *header;
} skiplist;

skiplist *skiplist_init(skiplist *list) {
    // Initialisation function defined for above skiplist structures.
    int i;

    // dyanamic allocation of memory of size struct node pointed by snode pointer(header)
    snode *header = (snode *) malloc(sizeof(struct snode)); 
    list->header = header;
    header->key = INT_MAX;
    header->forward = (snode **) malloc(sizeof(snode*) * (SKIPLIST_MAX_LEVEL + 1)); 
    // Initialising forward list for all header of skiplist levels
    for (i = 0; i <= SKIPLIST_MAX_LEVEL; i++) {
        header->forward[i] = list->header;
    }

    list->level = 1;
    list->size = 0;

    return list;
}

static int rand_level() {
    // This function will return an random integer(level) using builtin rand fuction
    int level = 1;
    while (rand() < RAND_MAX / 2 && level < SKIPLIST_MAX_LEVEL)
        level++;
    return level;
}

int skiplist_insert(skiplist *list, int key, int value) {
    snode *update[SKIPLIST_MAX_LEVEL + 1];
    snode *x = list->header;
    int i, level;
    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }
    x = x->forward[1];

    if (key == x->key) {
        x->value = value;
        return 0;
    } else {
        level = rand_level();
        if (level > list->level) {
            for (i = list->level + 1; i <= level; i++) {
                update[i] = list->header;
            }
            list->level = level;
        }

        x = (snode *) malloc(sizeof(snode));
        x->key = key;
        x->value = value;
        x->forward = (snode **) malloc(sizeof(snode*) * (level + 1));
        for (i = 1; i <= level; i++) {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
    }
    return 0;
}

snode *skiplist_search(skiplist *list, int key) {
    // This function will search for an key in the skiplist. It will return pointer to the key if found, else null pointer.
    snode *x = list->header; // a pointer of type snode is declared to traverse the given skiplist header.
    int i;

    // Traversing the levels of skiplist
    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key)
            x = x->forward[i];
    }

    if (x->forward[1]->key == key) {
        return x->forward[1]; // returns pointer to the key
    } else {
        return NULL;
    }
    return NULL;
}

static void skiplist_node_free(snode *x) {
    /* 
        this function would be used 
        to free a node whenever required.
        It takes a skiplist node as its arguement. 
    */
    if (x) {
        // it frees the forward list of the given header and header itself too.
        free(x->forward); 
        free(x);
    }
}

int skiplist_delete(skiplist *list, int key) {
    /* 
        this function will delete an element
        from the skiplist whose value will
        be equal to the value given as arguement.
        It takes skiplist and a key as its arguement.
        Returns 1 if succeed to delete that element, 
        or 0 if failed.
    */
    int i;
    snode *update[SKIPLIST_MAX_LEVEL + 1]; // array(update) of pointers of type snode is defined
    snode *x = list->header;    // pointer to the list header of type snode

    /* searching for the given key in skip list */
    for (i = list->level; i >= 1;  i--) {
        while (x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }

    x = x->forward[1];
    if (x->key == key) {
        for (i = 1; i <= list->level; i++) {
            if (update[i]->forward[i] != x)
                break;
            update[i]->forward[1] = x->forward[i];
        }
        skiplist_node_free(x); // it will free the skiplist node x.

        while (list->level > 1 && list->header->forward[list->level]== list->header)
            list->level--; 
        return 0; // returns 0 if any failure occurs during deletion
    }
    return 1; // returns 1 if the given key is successfully deleted
}

static void skiplist_dump(skiplist *list) {
    /*
        this function is defined to print
        all the elements present in skip list.
        It takes a list as parameter and doesn't
        return anything
    */
    snode *x = list->header; // skiplist node pointer is defined
    
    while (x && x->forward[1] != list->header) {
        /* 
            to print key and value pair of 
            elements present in skip list
        */
        printf("%d[%d]->", x->forward[1]->key, x->forward[1]->value);

        x = x->forward[1]; // to move pointer to the next node in skip list 
    }
    printf("NIL\n");
}
#define myheader
#endif
