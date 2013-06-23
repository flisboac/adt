
#ifndef DT_BASE_DEFS_H_
#define DT_BASE_DEFS_H_


#include <stddef.h>
#include "dtcfg.h"


/*##############################################################################
 * [[[   DEFINES   ]]]
 */


#define dt_NOSIZE ((size_t)-1)
#define dt_ISVALID(T, v) ((v) >= T ## _MIN && (v) <= T ## _MAX)
#define dt_EEcode_iswarn(x) (dt_EEcode_isvalid(x) && (x) < 0)
#define dt_EEcode_isvalid(t) dt_ISVALID(dt_EEcode, t)
#define dt_CAST(t, o) ((t)(o))
#define dt_CASTCALL(t, m, a) ((t) (m a))
#define dt_DCASTCALL(t, m, a) (* dt_CASTCALL(t, m, a))
#define dt_RCASTCALL(t, m, a) (& dt_CASTCALL(t, m, a))


/*##############################################################################
 * [[[   ENUMERATIONS   ]]]
 */


typedef enum dt_EEcode_    dt_EEcode;    /**< @see dt_EEcode_ */
typedef enum dt_EIterMode_ dt_EIterMode; /**< @see dt_EIterMode_ */
typedef enum dt_EValueAct_ dt_EValueAct; /**< @see dt_EValueAct_ */
typedef enum dt_ENature_   dt_ENature;   /**< @see dt_ENature_ */
typedef enum dt_ECtnrProp_ dt_ECtnrProp; /**< @see dt_ECtnrProp_ */
typedef enum dt_ERawType_  dt_ERawType;  /**< @see dt_ERawType_ */


/**
 * Represents a condition or exit code.
 *
 * Values greater than @c dt_OK are considered to be error
 * conditions, while values less than @c dt_OK are considered to be warning
 * or informational conditions.
 */
enum dt_EEcode_ {

      dt_ERRSIZE = -1 /**< The element reached its capacity limit. */
    , dt_OK      = 0  /**< Operation successful. */
    , dt_ERROR   = 1  /**< An error ocurred. */
    , dt_ERRNULL = 2  /**< Null pointer passed (somewhere). */
    , dt_ERRIMPL = 3  /**< Not implemented. */
    , dt_ERRSUPP = 4  /**< Not supported. */
    , dt_ERRMEM  = 5  /**< Out of memory. */
    , dt_ERRVAL  = 6  /**< Error while calling a value callback. */
    , dt_ERRMISS = 7  /**< Invalid or missing arguments or operands. */
    , dt_ERRCAP  = 8  /**< Insufficient capacty. */

    /* ... */

    , dt_EEcode_MAX = dt_ERRCAP
    , dt_EEcode_MIN = dt_ERRSIZE
};


/**
 * Represents an iterator's mode of container traversal.
 */
enum dt_EIterMode_ {

      dt_ITER_NONE = 0    /**< Invalid iterator or iteration mode. */
    , dt_ITER_ORDER       /**< Alias for an iteration in normal order (generally left-right). The specific mode is implementation-defined. */
    , dt_ITER_RORDER      /**< Alias for an iteration in reverse order. The specific mode is implementation-defined. */
    , dt_ITER_LEVEL_PRE   /**< Makes a pre-order, breadth-first iteration. */
    , dt_ITER_LEVEL_POST  /**< Makes a post-order, breadth-first iteration. */
    , dt_ITER_RLEVEL_PRE  /**< Makes a pre-order, breadth-first iteration, in reverse order. */
    , dt_ITER_RLEVEL_POST /**< Makes a post-order, breadth-first iteration, in reverse order. */
    , dt_ITER_DEPTH_LTR   /**< Makes a left-to-right, depth-first iteration. */
    , dt_ITER_DEPTH_RTL   /**< Makes a right-to-left, depth-first iteration. */
    , dt_ITER_RDEPTH_LTR  /**< Makes a left-to-right, depth-first iteration, in reverse order. */
    , dt_ITER_RDEPTH_RTL  /**< Makes a right-to-left, depth-first iteration, in reverse order. */

    /* ... */

    , dt_EIterMode_MAX = dt_ITER_RDEPTH_RTL
    , dt_EIterMode_MIN = dt_ITER_ORDER
};


/**
 * Enumeration of all possible actions on container keys or values.
 */
enum dt_EValueAct_ {

      dt_VAL_NONE = 0
    , dt_VAL_INIT
    , dt_VAL_QUIT
    , dt_VAL_COPY
    
    /* ... */
    
    , dt_EValueAct_MIN = dt_VAL_INIT
    , dt_EValueAct_MAX = dt_VAL_COPY
};


/**
 * Enumeration containing all valid container natures.
 */
enum dt_ENature_ {
    
      dt_NAT_ALL = -1
    , dt_NAT_NONE = 0
    
    , dt_NAT_LIST  /**< Container is a list of values. Indexing is done through a key with type @c size_t. */
    , dt_NAT_SET   /**< Container is a unique list of values. Sets should never declare a #dt_NAT_LIST nature. */
    , dt_NAT_MAP   /**< Container is an associative array. */
    , dt_NAT_BAG   /**< Container allows duplicate keys. */
    , dt_NAT_HASH  /**< Container is hash-based. */
    , dt_NAT_ARRAY /**< Container stores data contiguously in memory. */
    , dt_NAT_ORD   /**< Container is naturally ordered. */
    , dt_NAT_BIT   /**< Container is bit-oriented (instead of byte-oriented). */
    
    , dt_ENature_MIN = dt_NAT_LIST
    , dt_ENature_MAX = dt_NAT_BIT
};


/**
 * Enumeration containing all container properties.
 */
enum dt_ECtnrProp_ {
    
    dt_PROP_NONE = 0;
    
    , dt_PROP_ECODE     /* int */
    , dt_PROP_API       /* pointer */
    , dt_PROP_KTYPE     /* pointer */
    , dt_PROP_VTYPE     /* pointer */
    , dt_PROP_LEN       /* size_t */
    , dt_PROP_CAP       /* size_t */
    , dt_PROP_LOAD      /* size_t */
    , dt_PROP_DEFV      /* pointer */
    , dt_PROP_CAPMULT   /* size_t */
    , dt_PROP_ISWRAPPER /* int */
    , dt_PROP_ISMUTABLE /* int */
    , dt_PROP_FN        /* pointer */
    
    , dt_ECtnrProp_MIN = dt_PROP_OPTS
    , dt_ECtnrProp_MAX = dt_PROP_FN
};


/**
 * Enumeration of all possible raw types. If a type is based on an unlisted
 * raw type, use values that are less than 0, or #dt_RAW_CUSTOM.
 */
enum dt_ERawType_ {
    
    dt_RAW_POINTER = -4
    , dt_RAW_ARRAY
    , dt_RAW_VALUE
    , dt_RAW_CUSTOM
    , dt_RAW_NONE = 0
    
    , dt_RAW_CTNR
    , dt_RAW_ITER
    
    , dt_RAW_VOIDP
    , dt_RAW_SZ
    , dt_RAW_CSTR
    , dt_RAW_WSTR
    , dt_RAW_MBSTR
    
    , dt_RAW_CHAR
    , dt_RAW_INT
    , dt_RAW_LONG
    , dt_RAW_LLONG
    , dt_RAW_FLOAT
    , dt_RAW_DOUBLE
    
    , dt_ERawType_MIN = dt_RAW_CUSTOM
    , dt_ERawType_MAX = dt_RAW_DOUBLE
};


/*##############################################################################
 * [[[   TYPE DEFINITIONS   ]]]
 */

/* Basic types */
typedef struct dt_Type_ dt_Type; /**< @see dt_Type_ */
typedef struct dt_Ctnr_ dt_Ctnr; /**< @see dt_Ctnr_ */
typedef struct dt_Iter_ dt_Iter; /**< @see dt_Iter_ */

/* API Types */
typedef struct dt_CtnrApi_ dt_CtnrApi; /**< @see dt_CtnrApi_ */
typedef struct dt_IterApi_ dt_IterApi; /**< @see dt_IterApi_ */
typedef struct dt_Nature_  dt_Nature;  /**< @see dt_Nature_ */

/* Option types */
typedef struct dt_Opts_   dt_Opts;   /**< @see dt_Opts_ */
typedef struct dt_CtnrFn_ dt_CtnrFn; /**< @see dt_CtnrFn_ */
typedef struct dt_State_  dt_State;  /**< @see dt_State_ */

/* Value types */
typedef union dt_UValue_ dt_UValue; /**< @see dt_UValue_ */
typedef struct dt_Value_ dt_Value;  /**< @see dt_Value_ */

/* Helper Structures */
typedef struct dt_Buffer_    dt_Buffer;    /**< @see dt_Buffer_ */
typedef struct dt_Array_     dt_Array;     /**< @see dt_Array_ */
typedef struct dt_Pair_      dt_Pair;      /**< @see dt_Pair_ */
typedef struct dt_FlistNode_ dt_FlistNode; /**< @see dt_FlistNode_ */
typedef struct dt_ListNode_  dt_ListNode;  /**< @see dt_ListNode_ */
typedef struct dt_TreeNode_  dt_TreeNode;  /**< @see dt_TreeNode_ */


/**
 * A hashing function signature.
 * 
 * Represents a function that implements a hash of a specific value @c a of
 * type @c T. If the value cannot be hashed, or if an error occurred, #dt_NOSIZE
 * should be returned.
 * 
 * @c result is optional, and indicates the error outcome of the hashing
 * algorithm (if it executed with or without errors).
 */
typedef size_t (*dt_FHash)(dt_Type* T, dt_EEcode* result, const void* a);


/**
 * A comparison function signature.
 * 
 * Compares a value @c a with another value @b, both of type @c T, and returns
 * either -1 if a < b, 1 if a > b, or 0 if a == b or if the values are not
 * comparable.
 * 
 * Either way, @c result always indicates the error outcome of the comparison
 * (if it executed with or without errors). Passing it is optional.
 */
typedef int (*dt_FCmp)(dt_Type* T, dt_EEcode* result, const void *a, const void* b);


/**
 * A value event function signature.
 * 
 * Represents a function callback that will be called whenever an action is to
 * be taken on a value from a container. An enumeration of possible actions
 * is given by #dt_EValueAct.
 * 
 * Note that value action functions are used merely to initialize or finalize
 * values. Memory allocation is done by the containers, and happens outside
 * the function itself. It's advised that value action functions be reentrant
 * or does not introduce side-effects. @c valuep is there to supply some
 * state storage for value initializers, and it's best used when subtyping
 * standard (library-provided) types.
 * 
 * The action to execute is specified by @c act, together with the value in 
 * @c obj and its type in @c T. @c obj can represent a single value, or an
 * array of contiguous values, and in case of the latter, @c obj_count will be 
 * greater than 1. In case of copies (such as when #dt_VAL_COPY is passed to 
 * @c act), @c to must be a valid pointer to pre-allocated space of
 * @c obj_count elements, so that all objects on @c obj can be copied
 * into @c to.
 * 
 * @c valuep is a simple value pointer passed to the function
 * whenever it's called, and can be an external state used by the function's
 * implementation.
 * 
 */
typedef dt_EEcode (*dt_FValue)(void* valuep, dt_Type* T, dt_EValueAct act, size_t obj_count, void* obj, void* to);


/**
 * An event handler function signature.
 * 
 * Represents a function called when an adverse or special condition arises
 * in a container. Not all containers may have support for event handlers.
 * 
 * @c what indicates the exact event that occurred. It is complemented by 
 * @c ecode, which is an error code (see #dt_EEcode) associated
 * with the condition, and may further hint the nature of the condition.
 * 
 * @c C is the affected container.
 * 
 * If @c count is greater than zero, it indicates that the condition occurred
 * on a key or value on the container. In this case, @c count indicates whether
 * @c o holds a single element or more (contiguous in space).
 * 
 * @c isval indicates whether @c o is key or value.
 * 
 * The return value of the event function indicates what the container
 * algorithm should do.
 * - If the return value is 0, the event can be ignored. The algorithm can
 *   decide if it retries or ends the operation.
 * - If the return value is less than 0, the algorithm should retry the
 *   operation.
 * - If the return value is greater than 0, the algorithm should end the
 *   operation.
 */
typedef int (*dt_FEvent)(void* eventp, int what, dt_EEcode ecode, dt_Ctnr* C, size_t count, void* o, int isval);


/**
 * A memory allocation function signature.
 * 
 * The usage is similar to ANSI-C's @c realloc function, with some twists.
 * 
 * If @c o is NULL, the function will allocate @c bytesz bytes. In this case,
 * @c bytesz should be greater than 0, and if not, the behaviour can be
 * considered undefined.
 * 
 * If @c o is not NULL, then it must be a pointer to a block of memory 
 * previously allocated by the function. This block of memory will be
 * reallocated and have @c bytesz bytes, or be freed if @c bytesz is 0.
 * 
 * @c reason is an optional and merely informational argument used to
 * inform the allocator about the reason of the allocation (e.g. the type of
 * structure being allocated). Implementations can then have the opportunity to
 * catch, debug or analyze allocation behaviour.
 * 
 * There's an opportunity for implementations to use the combination
 * @code allocf(ptr, reason, NULL, 0) @endcode as a way to dispose the 
 * allocator and all of its allocated memory blocks. However, this can cause
 * serious problems (like deallocating blocks of memory still in use) and make
 * debugging troublesome if this behaviour was not intended by the callee.
 */
typedef void* (*dt_FAlloc)(void* allocp, int reason, void* o, size_t bytesz);


/*##############################################################################
 * [[[   STRUCTS AND UNIONS   ]]]
 */


/**
 * A structure representing a type.
 * As for sub-typing, if a value containing a @c NULL or @c 0 is found on
 * sub-types, the value will be looked up until it's found on any of the
 * sub-type's parent types.
 */
struct dt_Type_ {

    const dt_Type* base;    /**< Parent type, for creating sub-types. */
    dt_ERawType    rawtype; /**< The type's raw type. */
    const char*    name;    /**< A descriptive name for the type. */
    size_t         size;    /**< Total size of the type, in bytes.
                                 Must be greater than 0. */
    dt_FCmp        cmpf;    /**< The comparison function.
                                 @see dt_FCmp */
    dt_FHash       hashf;   /**< The hashing function.
                                 @see dt_FHash */
    dt_FValue      valuef;  /**< Value event function for keys or values.
                                 @see dt_FValue */
    void*          valuep;  /**< Optional state for #valuef. */
};


/**
 * TODO Documentation
 */
struct dt_CtnrFn_ {
    
    dt_FAlloc allocf;  /**< Memory allocation function. */
    void*     allocp;  /**< Optional state to be passed to @c allocf */
    dt_FEvent eventf;  /**< Optional event handler. */
    void*     eventp;  /**< Optional state to be passed to @c eventp */
    dt_Type*  type;    /**< Custom type for the container.
                            This is where comparison and hashing
                            functions will be taken from when a container
                            holds other containers. If NULL, #dt_ctnr_type
                            will be used. */
};


/**
 * TODO Documentation
 */
struct dt_State_ {
    
    dt_CtnrApi* api;       /**< Optional field used to determine if the state is
                                generic (@c api is @c NULL) or specific. */
    dt_EEcode   ecode;     /**< Used to set or return the state of a container. */
    dt_CtnrFn   fn;        /**< Stores container's functions. */
    dt_CtnrFn*  sharedfn;  /**< Stores shared container's functions. If not 
                                NULL, has higher priority than #fn. Used mainly
                                by container adaptors, to use the same set of
                                support functions like allocators and event
                                calbacks on all sub-containers. */
    size_t      capmult;   /**< Size multiplier.
                                When the container size reaches its
                                capacity, if @c capmult is greater than 0, the
                                container is automatically resized using its own
                                reserve method with a size equal to the current
                                capacity multiplied by @c capmult. Setting 
                                @c capmult to 1 effectively makes it a frozen
                                container (cannot grow in memory size, although
                                it can still compact memory).
                                The generic value is 2, for doubling the
                                size. A value of 0 is not valid. */
    int         iswrapper; /**< If 1, indicates that the container is a wrapper
                                for external data (probably @c const). As a
                                wrapper, the container does not own its inner
                                data, and therefore, does not deallocate it when
                                the container is disposed. */
    int         immutable; /**< If 1, the container cannot change its values.
                                It can still grow or shrink in memory, though.
                                The default option is 0, for mutable. */
};


/**
 * A structure used hold or inform container options.
 */
struct dt_Opts_ {

    dt_CtnrApi* api;       /**< Optional field used to determine if the state is
                                generic (@c api is @c NULL) or specific. */
    dt_Type*    ktype;     /**< The key's type, for associative containers. */
    dt_Type*    vtype;     /**< The value's type. */
    size_t      cap;       /**< Total capacity of the container in elements, or
                                #dt_NOSIZE if not applicable. A value of 0 has
                                effects that are implementation-defined. */
    size_t      len;       /**< Container's actual length, in elements, or
                                #dt_NOSIZE if not applicable. A value of 0 has
                                effects that are implementation-defined. */
    size_t      load;      /**< The load factor for hash-based containers, or
                                #dt_NOSIZE if not applicable. A value of 0 has
                                effects that are implementation-defined. */
    dt_CtnrFn   fn;        /**< Stores container's functions. */
    size_t      capmult;   /**< Size multiplier.
                                When the container size reaches its
                                capacity, if @c capmult is greater than 0, the
                                container is automatically resized using its own
                                reserve method with a size equal to the current
                                capacity multiplied by @c capmult. Setting 
                                @c capmult to 1 effectively makes it a frozen
                                container (cannot grow in memory size, although
                                it can still compact memory).
                                The generic value is 2, for doubling the
                                size. A value of 0 is not valid. */
    int         iswrapper; /**< If 1, indicates that the container is a wrapper
                                for external data (probably @c const). As a
                                wrapper, the container does not own its inner
                                data, and therefore, does not deallocate it when
                                the container is disposed. */
    int         immutable; /**< If 1, the container cannot change its values.
                                It can still grow or shrink in memory, though.
                                The default option is 0, for mutable. */
};


/**
 * Basic type for nature APIs.
 */
struct dt_Nature_ {
    
    dt_ENature nature;
};


/**
 * TODO Documentation
 */
struct dt_Buffer_ {
    
    size_t len; /**< Buffer length, in elements (NOT in bytes). */
    size_t cap; /**< Buffer capacity, in elements (NOT in bytes). */
    void*  ptr; /**< Buffer data. Must be cast to the proper type. */
};


/**
 * TODO Documentation
 */
struct dt_Array_ {
    
    size_t len; /**< Array length, in elements (NOT in bytes). */
    void*  ptr; /**< Array data. Must be cast to the proper type. */
};


/**
 * TODO Documentation
 */
struct dt_Pair_ {
    
    void* key;
    void* val;
};


/**
 * TODO Documentation
 */
struct dt_FlistNode_ {
    
    dt_FlistNode* next;
    void*         val;
};

/**
 * TODO Documentation
 */
struct dt_ListNode_ {
    
    dt_ListNode* prev;
    dt_ListNode* next;
    void*        val;
};


/**
 * TODO Documentation
 */
struct dt_TreeNode_ {
    
    dt_TreeNode* parent;
    dt_TreeNode* left;
    dt_TreeNode* right;
    void*        val;
};


/**
 * TODO Documentation
 */
union dt_UValue_ {
    
    /* C Language adt-supported types */
    
    char     char_v;
    wchar_t  wchar_v;
    int      int_v;
    long     long_v;
    float    float_v;
    double   double_v;
    size_t   sz_v;
    
    void*    voidp_v;
    char*    cstr_v;
    char*    mbstr_v;
    wchar_t* wstr_v;
    
    /* Own adt-supported types */
    
    dt_Ctnr* ctnr_v;
    dt_Iter* iter_v;
    dt_Type* type_v;
    
    /* User-defined types */
    
    void*    ptr;
};


/**
 * TODO Documentation
 */
struct dt_Value_ {
    
    dt_ERawType rawtype;
    dt_UValue   val;
};

#endif
