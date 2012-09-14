
#include <stddef.h>

adt_IDATA const adt_ECategory categories[][];
adt_IDATA const int implemented[];

/*
 * [ A U X I L I A R Y ] =======================================================
 */

typedef struct SingleBucket_t {
    
    int using;
    adt_UValue val;
} SingleBucket;

typedef struct PairBucket_t {
    
    int using;
    adt_UValue key;
    adt_UValue val;
} PairBucket;


/*
 * [ C O N T A I N E R S ] =====================================================
 */

/**
 * Base structure for all containers.
 */
struct adt_Container_t {
    
    adt_EType type;
    adt_EValueType vtype;
    adt_Value defaultval;
    size_t cap;
    adt_FAlloc allocf;
    adt_FFinalize finalizef;
    char immutable;
    size_t resizemult;
    int autofree;
    adt_EEcode ecode;
};


typedef struct Vector_t {
    
    adt_Container ctnr;
    size_t len;
    void *ary;
} Vector;

typedef struct Deque_t {
    
    adt_Container ctnr;
    size_t lcap;
    size_t llen;
    size_t rcap;
    size_t rlen;
    void *lary;
    void *rary;
} Deque;

typedef struct Vset_t {
    
    adt_Container ctnr;
    /* comofas? */
} Vset;

typedef struct Vmap_t {
    
    adt_Container ctnr;
    /* comofas? */
} Vmap;

typedef struct Hashset_t {
    
    adt_Container ctnr;
    SingleBucket **table;
    size_t load;
} Hashset;

typedef struct Hashmap_t {
    
    adt_Container ctnr;
    PairBucket **table;
    size_t load;
} Hashmap;

typedef struct Bitset_t {
    
    adt_Container ctnr;
    size_t len;
    unsigned char *ptr;
} Bitset;


/*
 * [ I T E R A T O R S ] =======================================================
 */

struct adt_Iterator_t {
    
    adt_Container *ctnr;
    int way;
    int started;
    adt_EEcode ecode;
};


typedef struct VectorIterator_t {
    
    adt_Iterator iter;
    size_t idx;
} VectorIterator;


typedef struct 
