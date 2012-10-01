#ifndef ADT_TYPES_H_
#define ADT_TYPES_H_

#include "adtdefs.h"
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

#define adt_NOPOS ((size_t)-1)

#define adt_Value_isvalid(v) adt_EValueType_isvalid(((adt_Value)(v)).vtype)
#define adt_EType_isvalid(t) ((t) > adt_TYPE_NONE && (t) < adt_TYPE_MAX)
#define adt_EValueType_isvalid(t) ((t) > adt_VTYPE_END && (t) < adt_VTYPE_MAX)
#define adt_EIteratorMode_isvalid(t) (t > adt_ITER_NONE && (t) < adt_ITER_MAX)

#define adt_UVALUE_DECL  \
    /* Library types */  \
    adt_Container *ctnr; \
    adt_Iterator *iter; \
    \
    /* Booleans */ \
    int b; \
    \
    /* Integers */ \
    char c; \
    unsigned char uc; \
    short int s; \
    unsigned short int us; \
    int i; \
    unsigned int ui; \
    long int l; \
    unsigned long int ul; \
    \
    /* Floats */ \
    float f; \
    double d; \
    long double ld; \
    \
    /* Pointers */ \
    void *vp; \
    char *cp; \
    wchar_t *wcp; \
    \
    /* stddef types */ \
    size_t sz; \
    ptrdiff_t pd; \
    wchar_t wc


typedef enum adt_EEcode_t adt_EEcode {
    
      adt_OK = 0  /**< Operation successful. */
    , adt_ERROR   /**< An error ocurred. */
    , adt_ERRIMPL /**< Not implemented. */
    , adt_ERRSUPP /**< Not supported. */
    , adt_ERRMEM  /**< Out of memory. */
    , adt_ERRMISS /**< Missing arguments or operands. */
    
    /* ... */
    
    , adt_ERRMAX     /**< Placeholder, for the maximum error code value. */
} adt_EEcode;

typedef enum adt_ECmpResult_t {
    
      adt_NC = -2  /**< Values are not comparable. */
    , adt_LT       /**< Value is less than another. */
    , adt_EQ       /**< Value is equals another. */
    , adt_GT       /**< Value is greater than another. */
} adt_ECmpResult;

typedef enum adt_EType_t {
    
      adt_TYPE_NONE = 0   /**< For cases where the container state is invalid. */
    , adt_TYPE_VECTOR     /**< A simple, contiguous array of values. */
    
    , adt_TYPE_MAX
} adt_EType;

typedef enum adt_ECategory_t {
    
      adt_CAT_NONE = 0 /**< The container does not fit in any category. */
    , adt_CAT_LIST     /**< Lists of ordered values. */
    , adt_CAT_SET      /**< Sets of unique values. */
    , adt_CAT_MAP      /**< Mapping of unique keys to arbitrary values. */
    , adt_CAT_BAG      /**< Mapping containers allowing duplicate keys. */
    , adt_CAT_HASHABLE /**< Indicates a hash-based container. */
    
    , adt_CAT_MAX
} adt_ECategory;

typedef enum adt_EValueType_t {
    
      adt_VTYPE_NONE = 0
    , adt_VTYPE_END
    , adt_VTYPE_CUSTOM
    , adt_VTYPE_CTNR
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

typedef enum adt_EIteratorMode_t {
    
      adt_ITER_NONE = 0
    , adt_ITER_ORDER
    , adt_ITER_RORDER
    , adt_ITER_LEVEL
    , adt_ITER_RLEVEL
    
    , adt_ITER_MAX
} adt_EIteratorMode;

typedef struct adt_Container_t adt_Container;
typedef struct adt_Iterator_t adt_Iterator;
typedef struct adt_ContainerApi_t adt_ContainerApi;
typedef struct adt_IteratorApi_t adt_IteratorApi;
typedef union adt_UValue_t adt_UValue;
typedef union adt_UPvalue_t adt_UPvalue;
typedef struct adt_Value adt_Value;

typedef union adt_UPvalue_t {
    
    void *ptr; /** Generic pointer. */
    
    adt_Container **ctnr;
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
    wchar_t **wcp;
    
    size_t *sz;
    ptrdiff_t *pd;
    wchar_t *wc;  
} adt_UPvalue;

typedef union adt_UValue_t {
    
    adt_UVALUE_DECL;
} adt_UValue;

typedef struct adt_Value_t {
    
    union {
        adt_UValue uvalue;
        adt_UVALUE_DECL;
    };
    adt_EValueType vtype;
    union {
        size_t esize;    /**< In case of pointers, tells the size, in bytes, of
                              the pointed element's type. Important mostly
                              for custom value types (@c adt_VTYPE_CUSTOM). */
    };
    size_t vsize;
} adt_Value;

typedef size_t (*adt_FHash)(adt_Value val);
typedef void* (*adt_FAlloc)(void *ptr, size_t sz);
typedef adt_Value (*adt_FIterate)(void *state, adt_Value val, ...);
typedef adt_ECmpResult (*adt_FCompare)(adt_Value obj, adt_Value other);
typedef void (*adt_FFinalize)(adt_Value value);

typedef struct adt_Options_t {
    
    adt_Value keytype;       /**< Value for the key, in case of maps. */
    adt_Value valtype;       /**< Value for maps, in case of lists or sets. */
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