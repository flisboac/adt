#ifndef ADT_TYPES_H_
#define ADT_TYPES_H_

#include <stddef.h>

/* Rationale:
 * - Ends in at: uses index
 * - Ends in on: uses keys (value keys)
 * 
- Lists:
    - Index is of type size_t
    - Value type given by the user
    - Operations:
        - get
        - set
        - insert
        - delete
        - remove
        - push/pop (left/right)
        - 
        
 */

/**
 * @ingroup adt_base_defs
 * @{
 */

/**
 * An invalid indexing position or hash value.
 */
#define adt_NOPOS ((size_t)-1)

#define adt_Value_isvalid(v) \
    adt_EValueType_isvalid((adt_Value)v.vtype)

#define adt_EType_isvalid(t) \
    (t > adt_TYPE_NONE && t < adt_TYPE_MAX)

#define adt_EValueType_isvalid(t) \
    (t > adt_VTYPE_END && t < adt_VTYPE_MAX)
    
#define adt_ECategory_isvalid(t) \
    (t > adt_CAT_NONE && t < adt_CAT_MAX)
 
#define adt_EIteratorMode_isvalid(t) \
    (t > adt_ITER_NONE && t < adt_ITER_MAX)
    
/**
 * Enumeration of all the library's error codes.
 */
typedef enum adt_EEcode_t {
    
      adt_EC_OK = 0  /**< Operation successful. */
    , adt_EC_ERROR   /**< An error ocurred. */
    , adt_EC_NIMPL   /**< Not implemented. */
    , adt_EC_NSUPP   /**< Not supported. */
    , adt_EC_NOMEM   /**< Out of memory. */
    , adt_EC_MISS    /**< Missing arguments or operands. */
    
    /* ... */
    
    , adt_EC_MAX     /**< Placeholder, for the maximum error code value. */
} adt_EEcode;

/**
 * Enumerates all possible results of a value comparison.
 */
typedef enum adt_ECmpResult_t {
    
      adt_CMP_ERR = -2  /**< Values are not comparable. */
    , adt_CMP_LT        /**< Value is less than another. */
    , adt_CMP_EQ        /**< Value is equals another. */
    , adt_CMP_GT        /**< Value is greater than another. */
} adt_ECmpResult;

/**
 * Enumeration of all the library's container types.
 */
typedef enum adt_EType_t {
    
      adt_TYPE_NONE = 0   /**< For cases where the container state is invalid. */
    , adt_TYPE_VECTOR     /**< A simple, contiguous array of values. */

#if 0
    , adt_TYPE_DLIST      /**< A doubly-linked list. */
    , adt_TYPE_DEQUE      /**< A vector-like container, with efficient
                               insertion and deletion at both ends. */
    , adt_TYPE_TREESET    /**< A list of unique elements. */
    , adt_TYPE_HASHSET    /**< A hash-based map. */
    , adt_TYPE_BAGTREESET /**< A multi-valoured set. */
    , adt_TYPE_BAGHASHSET /**< A multi-set implemented through hash values. */
    , adt_TYPE_TREEMAP    /**< A key-value associative mapping. */
    , adt_TYPE_HASHMAP    /**< A hash-based set. */
    , adt_TYPE_BAGTREEMAP /**< A multi-valoured key map. */
    , adt_TYPE_BAGHASHMAP /**< A multi-map implemented through hash values. */
#endif
    
    , adt_TYPE_MAX
} adt_EType;

/**
 * Enumeration of all categories of containers.
 */
typedef enum adt_ECategory_t {
    
      adt_CAT_NONE = 0 /**< The container does not fit in any category. */
    , adt_CAT_LIST     /**< Lists of ordered values. */
    , adt_CAT_SET      /**< Sets of unique values. */
    , adt_CAT_MAP      /**< Mapping of unique keys to arbitrary values. */
    , adt_CAT_BAG      /**< Mapping containers allowing duplicate keys. */
    , adt_CAT_TREE     /**< An ordered, parental-based tree of nodes. */
    , adt_CAT_GRAPH    /**< Space where nodes can have arbitrary associations between them.  */
    , adt_CAT_SEQ      /**< Indicates a sequential container. */
    , adt_CAT_ASSOC    /**< Indicates an associative container. */
    , adt_CAT_HASH     /**< Indicates a hash-based container. */
    
    , adt_CAT_MAX
} adt_ECategory;

/**
 * Enumeration of all the library's supported value types.
 */
typedef enum adt_EValueType_t {
    
      adt_VTYPE_NONE = 0
    , adt_VTYPE_END
    , adt_VTYPE_CUSTOM
    , adt_VTYPE_CTNR
    , adt_VTYPE_PAIR
    , adt_VTYPE_NODE
    , adt_VTYPE_ITER
    
    , adt_VTYPE_BOOL
    
    , adt_VTYPE_CHAR
    , adt_VTYPE_UCHAR
    , adt_VTYPE_SHORT
    , adt_VTYPE_USHORT
    , adt_VTYPE_INT
    , adt_VTYPE_UINT
    , adt_VTYPE_LONG
    , adt_VTYPE_ULONG
    
    , adt_VTYPE_FLOAT
    , adt_VTYPE_DOUBLE
    , adt_VTYPE_LDOUBLE
    
    , adt_VTYPE_VOIDP
    , adt_VTYPE_CHARP
    , adt_VTYPE_WCHARP
    
    , adt_VTYPE_SIZET
    , adt_VTYPE_PTRDT
    , adt_VTYPE_WCHAR
    
    , adt_VTYPE_MAX
} adt_EValueType;

/**
 * 
 */
typedef enum adt_EIteratorMode_t {
    
      adt_ITER_NONE = 0
    , adt_ITER_ORDER
    , adt_ITER_RORDER
    , adt_ITER_LEVEL
    , adt_ITER_RLEVEL
    
    , adt_ITER_MAX
} adt_EIteratorMode;

/**
 * @}
 * @ingroup adt_base_structs
 * @{
 */

/**
 * Opaque type to a generic container.
 * All other library functions will use pointers to this typedef.
 */
typedef struct adt_Container_t adt_Container;

/**
 * Type definition for @a adt_Pair_t.
 */
typedef struct adt_Pair_t adt_Pair;

/**
 * An opaque object used to hold the state of iteration over a collection.
 */
typedef struct adt_Iterator_t adt_Iterator;

/**
 * Represents nodes in a tree or graph container.
 */
typedef struct adt_Node_t adt_Node;

/**
 * Union of all supported pointers to value types.
 */
typedef union adt_UPvalue_t {
    
    void *ptr; /** Generic pointer. */
    
    adt_Container **ctnr;
    adt_Pair **pair;
    adt_Node **node;
    adt_Iterator **iter;
    
    int b;
    
    char *c;
    unsigned char *uc;
    short int *s;
    unsigned short int *us;
    int *i;
    unsigned int *ui;
    long int *l;
    unsigned long int *ul;
    
    float *f;
    double *d;
    long double *ld;
    
    void **vp;
    char **cp;
    wchar_t **wp;
    
    size_t *sz;
    ptrdiff_t *pd;
    wchar_t *w;  
} adt_UPvalue;

/**
 * Union of all supported value types.
 */
typedef union adt_UValue_t {
    
    /* Library types */
    adt_Container *ctnr;
    adt_Pair *pair;
    adt_Node *node;
    adt_Iterator *iter;

    /* Integers */
    char c;
    unsigned char uc;
    short int s;
    unsigned short int us;
    int i;
    unsigned int ui;
    long int l;
    unsigned long int ul;

    /* Floats */
    float f;
    double d;
    long double ld;

    /* Pointers */
    void *vp;
    char *cp;
    wchar_t *wp;

    /* stddef types */
    size_t sz;
    ptrdiff_t pd;
    wchar_t w;
} adt_UValue;

/**
 * Amalgamation of all supported value types.
 * Value passing is supposed to be done through these specialized objects.
 * They're meant to be passed by value, not by reference (to avoid having to
 * manage memory for simple values).
 */
typedef struct adt_Value_t {
    
    adt_UValue uvalue;
    adt_EValueType vtype;
    union {
        size_t esize;    /**< In case of pointers, tells the size, in bytes, of
                              the pointed element's type. Important mostly
                              for custom value types (@c adt_VTYPE_CUSTOM). */
    };
    suze_t vsize;
} adt_Value;

/**
 * A simple pair of values, used in some functions.
 */
struct adt_Pair_t {
    
    union {
        adt_Value key;
        size_t idx;
    };
    adt_Value val;
};

/**
 * Signature for a function that makes a hash out of a specific value.
 */
typedef size_t (*adt_FHash)(adt_Value val);

/**
 * Signature for a function that manages memory allocation and deallocation.
 * Its interface is the exact same as @c stdlib's @c realloc.
 */
typedef void* (*adt_FAlloc)(void *ptr, size_t sz);

/**
 * Signature for a function used to iterate over values in a collection.
 * The iterator function will be called several times until it produces a valid
 * value. The function can have a state, represented by @c state, where it can
 * store previous runs and use them in its calculations.
 * @c actual is the actual value in the iterator, and @c seq is the return
 * candidate.
 */
typedef adt_Value (*adt_FIterate)(void *state, adt_Value actual, adt_Value seq);

/**
 * Signature for a function that compares two values.
 * @see adt_ECmpResult
 */
typedef adt_ECmpResult (*adt_FCompare)(adt_Value obj, adt_Value other);

/**
 * Signature for a function that finalizes values.
 */
typedef void (*adt_FFinalize)(adt_Value value);

/**
 * An utility object to hold container creation parameters.
 */
typedef struct adt_Options_t {
    
    adt_EType type;          /**< Container type and implementation. */
    adt_Value ktype;         /**< Value for the key, in case of maps. */
    adt_Value vtype;         /**< Value for maps, in case of lists or sets. */
    size_t cap;              /**< Capacity of the container, in elements. */
    size_t len;              /**< Size of the container, in elements. */
    size_t load;             /**< Load factor. For hash-based containers */
    adt_Container *ctnr;     /**< The returned container. */
    adt_Container *from;     /**< Specifies a container to copy from. */
    adt_EEcode ecode;        /**< In case of errors, indicates what happened. */
    adt_Value defaultval;    /**< The default value returned when an index or
                                  key does not exist in the container. */
    adt_FAlloc allocf;       /**< The memory management function. */
    adt_FFinalize finalizef; /**< A finalizer for values and keys. */
    adt_FHash hashf;         /**< The hashing function. */
    adt_FCompare comparef;   /**< The comparison function. */
    size_t resizemult;       /**< The auto-resizing multiplier. Valid
                                  only if >1. */
    char immutable;          /**< If true, container is immutable. */
    int autofree;            /**< If true, automatically frees the collection
                                  after its use by a library's function.
                                  Good for chaining calls. */
    int autoorder;           /**< Automatic ordering of values. If >0, orders
                                  from bigger to smaller, and if <0, orders
                                  from smaller to bigger. Order is from the
                                  begin of the collection. */
    
} adt_Options;

#endif