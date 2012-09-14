
#include "adt.h"

adt_ECategory categories[][] = {
    /* adt_TYPE_NONE   */  {adt_CAT_NONE}
    /* adt_TYPE_BITSET */, {adt_CAT_LIST, adt_CAT_BIT, adt_CAT_NONE}
    /* adt_TYPE_VECTOR */, {adt_CAT_LIST, adt_CAT_NONE}
    /* adt_TYPE_DLIST  */, {adt_CAT_LIST, adt_CAT_NONE}
    /* adt_TYPE_DEQUE  */, {adt_CAT_LIST, adt_CAT_NONE}
    /* adt_TYPE_VSET   */, {adt_CAT_SET, adt_CAT_NONE}
    /* adt_TYPE_HSET   */, {adt_CAT_SET, adt_CAT_NONE}
    /* adt_TYPE_MSET   */, {adt_CAT_SET, adt_CAT_NONE}
    /* adt_TYPE_MHSET  */, {adt_CAT_SET, adt_CAT_BAG, adt_CAT_NONE}
    /* adt_TYPE_VMAP   */, {adt_CAT_MAP, adt_CAT_NONE}
    /* adt_TYPE_HMAP   */, {adt_CAT_MAP, adt_CAT_NONE}
    /* adt_TYPE_MMAP   */, {adt_CAT_MAP, adt_CAT_NONE}
    /* adt_TYPE_MHMAP  */, {adt_CAT_MAP, adt_CAT_BAG, adt_CAT_NONE}
};

int implemented[] = {
    /* adt_TYPE_NONE   */  0
    /* adt_TYPE_BITSET */, 0
    /* adt_TYPE_VECTOR */, 0
    /* adt_TYPE_DLIST  */, 0
    /* adt_TYPE_DEQUE  */, 0
    /* adt_TYPE_VSET   */, 0
    /* adt_TYPE_HSET   */, 0
    /* adt_TYPE_MSET   */, 0
    /* adt_TYPE_MHSET  */, 0
    /* adt_TYPE_VMAP   */, 0
    /* adt_TYPE_HMAP   */, 0
    /* adt_TYPE_MMAP   */, 0
    /* adt_TYPE_MHMAP  */, 0
}
