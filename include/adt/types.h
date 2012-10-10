/**
 * @file include/adt/types.h
 */

#ifndef ADT_TYPES_H_
#define ADT_TYPES_H_

#include "adtdef.h"
#include <stddef.h>

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


#define adt_VALUETYPE_DECL \
	/** The type of the value, be it for discrete values or pointer-based ones. \
	 */ \
	adt_EValueType vtype; \
	/** Number of elements in the value, for array-based types. \
	 * Must be 1 for non-array types, and 0 for invalid types. \
	 * Note: the @c v stands for @c vector, not @c value. */ \
	size_t vsize; \
	/** Size of each element in bytes. If 0, the type is invalid. */ \
	size_t esize


/**
 * Specifies the error code for an operation.
 */
typedef enum adt_EEcode_t {

      adt_OK = 0  /**< Operation successful. */
    , adt_ERROR   /**< An error ocurred. */
    , adt_ERRIMPL /**< Not implemented. */
    , adt_ERRSUPP /**< Not supported. */
    , adt_ERRMEM  /**< Out of memory. */
    , adt_ERRMISS /**< Invalid or missing arguments or operands. */

    /* ... */

    , adt_ERRMAX     /**< Placeholder, for the maximum error code value. */
} adt_EEcode;


/**
 * Represents the result of a comparison operation.
 * @see adt_FCompare
 */
typedef enum adt_ECmpResult_t {

      adt_NC = -2  /**< Values are not comparable. */
    , adt_LT       /**< Value is less than another. */
    , adt_EQ       /**< Value is equals another. */
    , adt_GT       /**< Value is greater than another. */
} adt_ECmpResult;


/**
 * Enumeration of all container categories.
 */
typedef enum adt_ECategory_t {

      adt_CAT_NONE = 0 /**< The container does not fit in any category. */
    , adt_CAT_LIST     /**< Lists of ordered values. */
    , adt_CAT_SET      /**< Sets of unique values. */
    , adt_CAT_MAP      /**< Mapping of unique keys to arbitrary values. */
    , adt_CAT_BAG      /**< Mapping containers allowing duplicate keys. */
    , adt_CAT_HASHABLE /**< Indicates a hash-based container. */

    /* ... */

    , adt_CAT_MAX      /**< Placeholder, for the maximum category value. */
} adt_ECategory;


/**
 * Enumeration of all possible value types.
 */
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

    /* ... */

    , adt_VTYPE_MAX
} adt_EValueType;


/**
 * Indicates the iteration mode of an iterator.
 */
typedef enum adt_EIteratorMode_t {

      adt_ITER_NONE = 0  /**< Invalid iterator or iteration mode. */
    , adt_ITER_ORDER     /**< Iterates in normal order (generally left-right). */
    , adt_ITER_RORDER    /**< Iterates in reverse order. */
    , adt_ITER_LEVEL     /**< Iterates in normal order, respecting levels. */
    , adt_ITER_RLEVEL    /**< Iterates in reverse order, respecting levels. */

    /** ... */

    , adt_ITER_MAX       /**< Placeholder, for the maximum iteration mode value. */
} adt_EIteratorMode;


typedef struct adt_Container_t adt_Container;       /** @see adt_Container_t */
typedef struct adt_Iterator_t adt_Iterator;         /** @see adt_Iterator_t */
typedef struct adt_ContainerApi_t adt_ContainerApi; /** @see adt_ContainerApi_t */
typedef struct adt_IteratorApi_t adt_IteratorApi;   /** @see adt_IteratorApi_t */
typedef struct adt_ValueType_t adt_ValueType;       /** @see adt_ValueType_t */
typedef union adt_UValue_t adt_UValue;              /** @see adt_UValue_t */
typedef union adt_UPvalue_t adt_UPvalue;            /** @see adt_UPvalue_t */
typedef struct adt_Value_t adt_Value;               /** @see adt_Value */
typedef struct adt_Options_t adt_Options;           /** @see adt_Options_t */


typedef size_t (*adt_FHash)(adt_Value val);
typedef void* (*adt_FAlloc)(void* state, void *ptr, size_t sz, size_t align);
typedef adt_Value (*adt_FIterate)(void *state, adt_Value val, ...);
typedef adt_ECmpResult (*adt_FCompare)(adt_Value obj, adt_Value other);
typedef void (*adt_FFinalize)(adt_Value value);


/**
 * Union with all pointers for all valid types.
 */
union adt_UPvalue_t {

    void *ptr; /**< Generic pointer. */

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
};


/**
 * Union of all valid types.
 */
union adt_UValue_t {

    adt_UVALUE_DECL;
};


/**
 * Represents a value's type.
 */
struct adt_ValueType_t {

	adt_VALUETYPE_DECL;
};


/**
 * A structure aggregating both @a adt_UValue and @a adt_ValueType.
 */
struct adt_Value_t {

    union {
        adt_UValue uvalue;
        adt_UVALUE_DECL;
    };

    union {
    	adt_ValueType type;
    	adt_VALUETYPE_DECL;
    };
};


/**
 * A structure containing basic options identified by all containers.
 * Custom implementations can provide their own option structures, as long as
 * these have @a adt_Options_t as the first field.
 */
struct adt_Options_t {

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
    int autoorder;           /**< Automatic ordering of values. If >0, orders
                                  from bigger to smaller, and if <0, orders
                                  from smaller to bigger. Order is from the
                                  begin of the collection. */

};


#endif /* ADT_TYPES_H_ */
