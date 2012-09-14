#ifndef ADT_H_
#define ADT_H_

#include <stddef.h>
#include "adtdefs.h"


/* Rationale:
 * - Ends in at: uses index
 * - Ends in on: uses keys (value keys)
 * 
 *  
 */

/**
 * @ingroup adt_base_defs
 * @{
 */

/**
 * An invalid indexing position or hash value.
 */
#define adt_NOPOS ((size_t)-1)

/**
 * Enumeration of all the library's error codes.
 */
typedef enum adt_EEcode_t {
    
      adt_EC_OK = 0  /**< Operation successful. */
    , adt_EC_ERROR   /**< An error ocurred. */
    , adt_EC_NIMPL   /**< Not implemented. */
    , adt_EC_NSUPP   /**< Not supported. */
    , adt_EC_NOMEM   /**< Out of memory. */
    
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
    
      adt_TYPE_NONE    /**< For cases where the container state is invalid. */
    , adt_TYPE_BITSET  /**< A set of bits, akin to C++ STL's bitset. */
    , adt_TYPE_VECTOR  /**< A simple, contiguous array of values. */
    , adt_TYPE_DLIST   /**< A doubly-linked list. */
    , adt_TYPE_DEQUE   /**< A vector-like container, with efficient
                            insertion and deletion at both ends. */
    , adt_TYPE_VSET    /**< A list of unique elements. */
    , adt_TYPE_HSET    /**< A hash-based map. */
    , adt_TYPE_MSET    /**< A multi-valoured set. */
    , adt_TYPE_MHSET   /**< A multi-set implemented through hash values. */
    , adt_TYPE_VMAP    /**< A key-value associative mapping. */
    , adt_TYPE_HMAP    /**< A hash-based set. */
    , adt_TYPE_MMAP    /**< A multi-valoured key map. */
    , adt_TYPE_MHMAP   /**< A multi-map implemented through hash values. */
} adt_EType;

/**
 * Enumeration of all categories of containers.
 */
typedef enum adt_ECategory_t {
    
      adt_CAT_NONE  /**< The container does not fit in any category. */
    , adt_CAT_BIT   /**< Exclusive for bitsets. */
    , adt_CAT_LIST  /**< Lists of ordered values. */
    , adt_CAT_SET   /**< Lists of unique values. */
    , adt_CAT_MAP   /**< Mapping of unique keys to arbitrary values. */
    , adt_CAT_BAG   /**< Mapping containers allowing duplicate keys. */
} adt_ECategory;

/**
 * Enumeration of all the library's supported value types.
 */
typedef enum adt_EValueType_t {
    
      adt_VTYPE_NONE = 0
    , adt_VTYPE_END
    , adt_VTYPE_NULL
    , adt_VTYPE_CUSTOM
    , adt_VTYPE_CTNR
    , adt_VTYPE_PAIR
    , adt_VTYPE_ITER
    
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
} adt_EValueType;


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
 * Union of all supported pointers to value types.
 */
typedef union adt_UPvalue_t {
    
    void *ptr; /** Generic pointer. */
    
    adt_Container **ctnr;
    adt_Pair **pair;
    adt_Iterator **iter;
    
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
    
    adt_EValueType vtype;
    union {
        size_t vsize;    /**< In case of pointers, tells the size, in bytes, of
                              the pointed element's type. Important mostly
                              for custom value types (@c adt_VTYPE_CUSTOM). */
    };
    adt_UValue uvalue;
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
    
    adt_Container *from;     /**< Specifies a container to copy from. */
    adt_EType type;          /**< Container type and implementation. */
    adt_EValueType ktype;    /**< Value for the key, in case of maps. */
    adt_EValueType vtype;    /**< Value for maps, in case of lists or sets. */
    size_t ksize;
    size_t vsize;
    adt_Value defaultval;    /**< The default value returned when an index or
                                  key does not exist in the container. */
    size_t cap;              /**< Capacity of the container, in elements. */
    size_t len;              /**< Size of the container, in elements. */
    size_t load;             /**< Load factor. For hash-based containers */
    adt_FHash hashf;         /**< The hashing function. */
    adt_FAlloc allocf;       /**< The memory management function. */
    adt_FCompare comparef;   /**< The comparison function. */
    adt_FFinalize finalizef; /**< A finalizer for values and keys. */
    char immutable;          /**< If true, container is immutable. */
    size_t resizemult;       /**< The auto-resizing multiplier. Valid
                                  only if >1. */
    int autofree;            /**< If true, automatically frees the collection
                                  after its use by a library's function.
                                  Good for chaining calls. */
    int autoorder;          /**< Automatic ordering of values. If >0, orders
                                  from bigger to smaller, and if <0, orders
                                  from smaller to bigger. Order is from the
                                  begin of the collection. */
    
    adt_EEcode ecode;        /**< In case of errors, indicates what happened. */
} adt_Options;


/**
 * @}
 * @ingroup adt_base_misc
 * @{
 */

adt_API int adt_fitscategory(adt_EType ctype, adt_ECategory cat);
adt_API adt_ECategory[] adt_getcategories(adt_ECtype ctype);
adt_API adt_Options* adt_initoptions(adt_Options *options);
adt_API adt_Options* adt_copyoptions(adt_Options *from, adt_Options *to);
adt_API size_t adt_getmaxlenfor(adt_EType ctype);
adt_API adt_ECmpResult adt_valuecompare(adt_Value obj, adt_Value other);
adt_API size_t adt_valuehash(adt_Value val);

/**
 * @}
 * @ingroup adt_base_new
 * @{
 */

adt_API adt_Container *adt_new(adt_EType ctype);
adt_API adt_Container *adt_newwith(adt_Options *options);
adt_API adt_Container *adt_newfrom(adt_Container *C, adt_EType ctype);
adt_API void adt_free(adt_Container *C);
adt_API adt_Container *adt_copy(adt_Container *C);

/**
 * @}
 * @ingroup adt_base_access
 * @{
 */

/* Bitset */
adt_API adt_EEcode adt_bsetat(adt_Container *C, ...);
adt_API adt_EEcode adt_bclearat(adt_Container *C, ...);
adt_API adt_EEcode adt_btoggleat(adt_Container *C, ...);
adt_API adt_EEcode adt_bset(adt_Container *C);
adt_API adt_EEcode adt_bclear(adt_Container *C);
adt_API adt_EEcode adt_btoggle(adt_Container *C);
adt_API int adt_bget(adt_Container *C, ...);
adt_API size_t adt_bcount(adt_Container *C);
adt_API const unsigned char* adt_bgetptr(adt_Container *C);

/* Has */
adt_API size_t adt_has(adt_Container *C, ...);
adt_API size_t adt_hasat(adt_Container *C, ...);
adt_API size_t adt_hasvalue(adt_Container *C, ...);

/* Get */
adt_API adt_Value adt_at(adt_Container *C, ...);
adt_API adt_Value adt_on(adt_Container *C, ...);

/* Set */
adt_API adt_Value adt_setat(adt_Container *C, adt_Value val, ...);
adt_API adt_Value adt_seton(adt_Container *C, adt_Value val, ...);

/* Push */
adt_API adt_EEcode adt_push(adt_Container *C, adt_Value val);
adt_API adt_EEcode adt_pushl(adt_Container *C, adt_Value val);
adt_API adt_EEcode adt_pushr(adt_Container *C, adt_Value val);
adt_API adt_Value adt_pop(adt_Container *C);
adt_API adt_Value adt_popl(adt_Container *C);
adt_API adt_Value adt_popr(adt_Container *C);

/* Insertion */
adt_API adt_EEcode adt_insertat(adt_Container *C, adt_Value val, ...);
adt_API adt_EEcode adt_inserton(adt_Container *C, adt_Value val, ...);
adt_API adt_Value adt_removeat(adt_Container *C, ...);
adt_API adt_Value adt_removeon(adt_Container *C, ...);

/* Indexof */
adt_API adt_Value adt_index(adt_Container *C, adt_Value val);
adt_API size_t adt_indexat(adt_Container *C, adt_Value val);
adt_API adt_Value adt_rindex(adt_Container *C, adt_Value val);
adt_API size_t adt_rindexat(adt_Container *C, adt_Value val);

/* Shifts */
adt_API adt_EEcode adt_shiftl(adt_Container *C); /* Fills with default */
adt_API adt_EEcode adt_shiftr(adt_Container *C);
adt_API adt_EEcode adt_sshiftl(adt_Container *C); /* Circular shift */
adt_API adt_EEcode adt_sshiftr(adt_Container *C);

/**
 * @}
 * @ingroup adt_base_gen
 * @{
 */

adt_API adt_Container* adt_dup(adt_Container *C);
adt_API adt_EEcode adt_getkeys(adt_Container *C, adt_Container O);
adt_API adt_EEcode adt_getvalues(adt_Container *C, adt_Container O);
adt_API adt_EEcode adt_gethead(adt_Container *C, adt_Container *O);
adt_API adt_EEcode adt_gettail(adt_Container *C, adt_Container *O);
adt_API adt_EEcode adt_getrangeat(adt_Container *C, adt_Container *O, size_t from, size_t to);
adt_API adt_EEcode adt_getirange(adt_Container *O, adt_Iterator *from, adt_Iterator *to);

/**
 * @}
 * @ingroup adt_base_oper
 * @{
 */


/**
 * @}
 * @ingroup adt_base_action
 * @{
 */

adt_API adt_EEcode adt_sort(adt_Container *C);
adt_API adt_EEcode adt_resize(adt_Container *C, size_t sz);
adt_API adt_EEcode adt_reserve(adt_Container *C, size_t sz);
adt_API adt_EEcode adt_swap(adt_Container *C, adt_Container *O);
adt_API adt_EEcode adt_clear(adt_Container *C);

/**
 * @}
 * @ingroup adt_base_val
 * @{
 */

adt_API adt_Value adt_Value_none();
adt_API adt_Value adt_Value_null();
adt_API adt_Value adt_Value_end();
#define adtNONE adt_Value_none
#define adtNULL adt_Value_null
#define adtEND adt_Value_end

adt_API adt_Value adt_Value_container(adt_Container *C);
adt_API adt_Value adt_Value_pair(adt_Pair *P);
adt_API adt_Value adt_Value_iterator(adt_Iterator *I);
#define adtCTNR(C) adt_Value_container(C)
#define adtPAIR(P) adt_Value_pair(P)
#define adtITER(I) adt_Value_iterator(I)

adt_API adt_Value adt_Value_char(char c);
adt_API adt_Value adt_Value_uchar(unsigned char uc);
adt_API adt_Value adt_Value_short(short int s);
adt_API adt_Value adt_Value_ushort(unsigned short int us);
adt_API adt_Value adt_Value_int(int i);
adt_API adt_Value adt_Value_uint(unsigned int ui);
adt_API adt_Value adt_Value_long(long int l);
adt_API adt_Value adt_Value_ulong(unsigned long int ul);
#define adtC(x) adt_Value_char(x)
#define adtUC(x) adt_Value_uchar(x)
#define adtS(x) adt_Value_short(x)
#define adtUS(x) adt_Value_ushort(x)
#define adtI(x) adt_Value_int(x)
#define adtUI(x) adt_Value_uint(x)
#define adtL(x) adt_Value_long(x)
#define adtUL(x) adt_Value_ulong(x)

adt_API adt_Value adt_Value_float(float f);
adt_API adt_Value adt_Value_double(double d);
adt_API adt_Value adt_Value_ldouble(long double ld);
#define adtF(x) adt_Value_float(x)
#define adtD(x) adt_Value_double(x)
#define adtLD(x) adt_Value_ldouble(x)

adt_API adt_Value adt_Value_voidp(void *vp);
adt_API adt_Value adt_Value_charp(char *cp);
adt_API adt_Value adt_Value_wcharp(wchar_t wcp);
#define adt_VP(x) adt_Value_voidp(x)
#define adt_CP(x) adt_Value_charp(x)
#define adt_WP(x) adt_Value_wcharp(x)

adt_API adt_Value adt_Value_sizet(size_t sz);
adt_API adt_Value adt_Value_ptrdiff(ptrdiff_t pd);
adt_API adt_Value adt_Value_wchar(wchar_t wc);
#define adtSZ(x) adt_Value_sizet(x)
#define adtPD(x) adt_Value_ptrdiff(x)
#define adtW(x) adt_Value_wchar(x)

#define adt1() adtI(1)
#define adt0() adtI(0)

/**
 * @}
 * @ingroup adt_base_state
 * @{
 */

adt_API void adt_getoptions(adt_Container *C, adt_Options *to);
adt_API adt_EEcode adt_getecode(adt_Container *C);
adt_API adt_ECategory adt_getcategory(adt_Container *C);
adt_API size_t adt_getlen(adt_Container *C);
adt_API size_t adt_getcap(adt_Container *C);
adt_API size_t adt_getcount(adt_Container *C);

adt_API int adt_canresize(adt_Container *C);
adt_API int adt_canchange(adt_Container *C);
adt_API int adt_isempty(adt_Container *C);
adt_API int adt_isautofree(adt_Container *C);
adt_API int adt_isautoorder(adt_Container *C);

adt_API adt_EEcode adt_setimmutable(adt_Container *C);
adt_API int adt_setresizemult(adt_Container *C, size_t mult);
adt_API adt_EEcode adt_setautofree(adt_Container *C, int flag);
adt_API adt_EEcode adt_setautoorder(adt_Container *C, int flag);
adt_API adt_EEcode adt_sethashf(adt_Container *C, adt_FHash hashf);
adt_API adt_EEcode adt_setfinalizerf(adt_Container *C, adt_FFinalize finalizef);
adt_API adt_EEcode adt_setcomparef(adt_Container *C, adt_FCompare hashf);

/**
 * @}
 * @ingroup adt_base_iter Iterators
 * @{
 */

adt_API adt_Iterator* adt_ibegin(adt_Container *C, int autofree);
adt_API adt_Iterator* adt_iend(adt_Container *C, int autofree);
adt_API adt_Iterator* adt_irbegin(adt_Container *C, int autofree);
adt_API adt_Iterator* adt_irend(adt_Container *C, int autofree);
adt_API adt_Iterator* adt_ibeginat(adt_Container *C, int autofree, ...);
adt_API adt_Iterator* adt_irbeginat(adt_Container *C, int autofree, ...);
adt_API adt_Iterator* adt_ibeginon(adt_Container *C, int autofree, ...);
adt_API adt_Iterator* adt_irbeginon(adt_Container *C, int autofree, ...);

adt_API adt_Value adt_Iterator_actual(adt_Iterator *I);
adt_API adt_Value adt_Iterator_next(adt_Iterator *I);
adt_API adt_Value adt_Iterator_previous(adt_Iterator *I);
adt_API int adt_Iterator_hasstarted(adt_Iterator *I);
adt_API int adt_Iterator_hasnext(adt_Iterator *I);
adt_API int adt_Iterator_hasprevious(adt_Iterator *I);
adt_API int adt_Iterator_getdirection(adt_Iterator *I);
adt_API int adt_Iterator_compare(adt_Iterator *I, adt_Iterator *O);
adt_API adt_Container* adt_Iterator_getcontainer(adt_Iterator *I);
adt_API adt_Value adt_Iterator_getvalue(adt_Iterator *I);
adt_API adt_EEcode adt_Iterator_getecode(adt_Iterator *I);
adt_API adt_EEcode adt_Iterator_remove(adt_Iterator *I);
adt_API adt_EEcode adt_Iterator_setvalue(adt_Iterator *I, adt_Value val);
adt_API void adt_Iterator_free(adt_Iterator *I);

#define adt_iactual(i) adt_Iterator_actual(i)
#define adt_inext(i) adt_Iterator_next(i)
#define adt_iprev(i) adt_Iterator_previous(i)
#define adt_istarted(i) adt_Iterator_hasnext(i)
#define adt_ihasnext(i) adt_Iterator_hasnext(i)
#define adt_ihasprev(i) adt_Iterator_hasprevious(i)
#define adt_igetctnr(i) adt_Iterator_getcontainer(i)
#define adt_igetdir(i) adt_Iterator_getdirection(i)
#define adt_icmp(i, o) adt_Iterator_compare(i, o)
#define adt_igetval(i) adt_Iterator_getvalue(i)
#define adt_igetecode(i) adt_Iterator_geterror(i)
#define adt_iremove(i) adt_Iterator_remove(i)
#define adt_isetval(i, v) adt_Iterator_setvalue(i, v)
#define adt_ifree(i) adt_Iterator_free(i)

/** @} */

#endif

