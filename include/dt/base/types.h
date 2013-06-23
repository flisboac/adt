
#ifndef DT_BASE_TYPES_H_
#define DT_BASE_TYPES_H_


#include <stddef.h>
#include "dtcfg.h"
#include "dt/base/defs.h"


/*##############################################################################
 * [[[   ENUMERATIONS   ]]]
 */

typedef enum dt_ECtnrOper_     dt_ECtnrOper;     /**< @see dt_ECtnrOper_ */
typedef enum dt_EIterOper_     dt_EIterOper;     /**< @see dt_EIterOper_ */
typedef enum dt_EStrCmpMethod_ dt_EStrCmpMethod; /**< @see dt_EStrCmpMethod_ */


/**
 * TODO Documentation
 */
enum dt_ECtnrOper_ {
    
      dt_OPER_NONE = 0 /**< Invalid operation code. */
      
    /* ALLOCATION */
    
    , dt_OPER_ASPECT_ALLOC = 50
    , dt_OPER_INIT /**< Calls the container's constructor. @see dt_OPER_ASPECT_ALLOC */
    , dt_OPER_NEW  /**< Allocation followed by #dt_OPER_INIT. @see dt_OPER_ASPECT_ALLOC */
    , dt_OPER_DUP  /**< Duplicates a container. @see dt_OPER_ASPECT_ALLOC */
    , dt_OPER_SWAP /**< Swap internal contents between containers. @see dt_OPER_ASPECT_ALLOC */
    , dt_OPER_QUIT /**< Calls the container's destructor. @see dt_OPER_ASPECT_ALLOC */
    , dt_OPER_FREE /**< Destruction followed by deallocation. @see dt_OPER_ASPECT_ALLOC */
    , dt_ECtnrOper_ALLOC_MIN = dt_OPER_INIT
    , dt_ECtnrOper_ALLOC_MAX = dt_OPER_FREE
    
    /* OPERATIONS */
    
    , dt_OPER_ASPECT_OPER = 100
    , dt_OPER_SORT    /**< TODO Documentation. @see dt_OPER_ASPECT_OPER */
    , dt_OPER_RESERVE /**< TODO Documentation. @see dt_OPER_ASPECT_OPER */
    , dt_OPER_RESIZE  /**< TODO Documentation. @see dt_OPER_ASPECT_OPER */
    , dt_OPER_REHASH  /**< TODO Documentation. @see dt_OPER_ASPECT_OPER */
    , dt_OPER_CLEAR   /**< TODO Documentation. @see dt_OPER_ASPECT_OPER */
    , dt_OPER_REVERSE /**< TODO Documentation. @see dt_OPER_ASPECT_OPER */
    , dt_OPER_ZIP     /**< TODO Documentation. @see dt_OPER_ASPECT_OPER */
    , dt_ECtnrOper_OPER_MIN = dt_OPER_RESERVE
    , dt_ECtnrOper_OPER_MAX = dt_OPER_REVERSE
    
    /* STATE */
    
    , dt_OPER_ASPECT_STATE = 150
    , dt_OPER_GETSTATE /**< TODO Documentation. @see dt_OPER_ASPECT_STATE */
    , dt_OPER_SETSTATE /**< TODO Documentation. @see dt_OPER_ASPECT_STATE */
    , dt_OPER_GETPROP  /**< TODO Documentation. @see dt_OPER_ASPECT_STATE */
    , dt_OPER_SETPROP  /**< TODO Documentation. @see dt_OPER_ASPECT_STATE */
    , dt_OPER_GETLEN   /**< TODO Documentation. @see dt_OPER_ASPECT_STATE */
    , dt_OPER_GETCAP   /**< TODO Documentation. @see dt_OPER_ASPECT_STATE */
    , dt_ECtnrOper_STATE_MIN = dt_OPER_GETSTATE
    , dt_ECtnrOper_STATE_MAX = dt_OPER_GETLOAD
    
    /* DATA ACCESS */
    
    , dt_OPER_ASPECT_DATA = 200
    , dt_OPER_HAS      /**< Returns true if a key exists in the container. @see dt_OPER_ASPECT_DATA */
    , dt_OPER_HASC     /**< Returns the number of ocurrences of a key. @see dt_OPER_ASPECT_DATA */
    , dt_OPER_GET      /**< TODO Documentation. @see dt_OPER_ASPECT_DATA */
    , dt_OPER_PUT      /**< TODO Documentation. @see dt_OPER_ASPECT_DATA */
    , dt_OPER_SET      /**< TODO Documentation. @see dt_OPER_ASPECT_DATA */
    , dt_OPER_INSERT   /**< TODO Documentation. @see dt_OPER_ASPECT_DATA */
    , dt_OPER_REMOVE   /**< TODO Documentation. @see dt_OPER_ASPECT_DATA */
    , dt_OPER_FLIP     /**< TODO Documentation. @see dt_OPER_ASPECT_DATA */
    , dt_OPER_RESET    /**< TODO Documentation. @see dt_OPER_ASPECT_DATA */
    , dt_OPER_BITTEST  /**< TODO Documentation. @see dt_OPER_ASPECT_DATA */
    , dt_OPER_BITON    /**< TODO Documentation. @see dt_OPER_ASPECT_DATA */
    , dt_OPER_BITOFF   /**< TODO Documentation. @see dt_OPER_ASPECT_DATA */
    , dt_OPER_BITFLIP  /**< TODO Documentation. @see dt_OPER_ASPECT_DATA */
    , dt_OPER_BITRESET /**< TODO Documentation. @see dt_OPER_ASPECT_DATA */
    , dt_OPER_BITCOUNT /**< TODO Documentation. @see dt_OPER_ASPECT_DATA */
    , dt_ECtnrOper_DATA_MIN = dt_OPER_HAS
    , dt_ECtnrOper_DATA_MAX = dt_OPER_BITCOUNT
    
    /* SHIFTING */
    
    , dt_OPER_ASPECT_SHIFT = 250
    , dt_OPER_POP   /**< Pops the last element, in default order. @see dt_OPER_ASPECT_SHIFT */
    , dt_OPER_POPI  /**< Pops the last element, in reverse order. @see dt_OPER_ASPECT_SHIFT */
    , dt_OPER_PUSH  /**< Pushes an element to the container, in default order. @see dt_OPER_ASPECT_SHIFT */
    , dt_OPER_PUSHI /**< Pushes an element to the container, in reverse order. @see dt_OPER_ASPECT_SHIFT */
    , dt_OPER_ROT   /**< Rotates and removes elements in the container, in default order. @see dt_OPER_ASPECT_SHIFT */
    , dt_OPER_ROTI  /**< Rotates and removes elements in the container, in reverse order. @see dt_OPER_ASPECT_SHIFT */
    , dt_OPER_CROT  /**< Rotates and re-inserts elements in the container, in default order. @see dt_OPER_ASPECT_SHIFT */
    , dt_OPER_CROTI /**< Rotates and re-inserts elements in the container, in reverse order. @see dt_OPER_ASPECT_SHIFT */
    , dt_ECtnrOper_SHIFT_MIN = dt_OPER_POP
    , dt_ECtnrOper_SHIFT_MAX = dt_OPER_CROTI
    
    /* ITERATION */
    
    , dt_OPER_ASPECT_ITER = 300
    , dt_OPER_ITER   /**< TODO Documentation. @see dt_OPER_ASPECT_ITER */
    , dt_OPER_ITERAT /**< TODO Documentation. @see dt_OPER_ASPECT_ITER */
    , dt_ECtnrOper_ITER_MIN = dt_OPER_ITER
    , dt_ECtnrOper_ITER_MAX = dt_OPER_ITERAT
    
    , dt_ECtnrOper_MIN = dt_ECtnrOper_ALLOC_MIN
    , dt_ECtnrOper_MAX = dt_ECtnrOper_ITER_MAX
};


/**
 * TODO Documentation
 */
enum dt_EIterOper_ {
    
      dt_IOPER_NONE = 0  /**< Invalid operation code. */
     
    /* Creation and Disposal */
    
    , dt_IOPER_ASPECT_ALLOC = 100
    , dt_IOPER_DISPOSE /**< TODO Documentation. @see dt_IOPER_ASPECT_ALLOC */
    , dt_EIterOper_ALLOC_MIN = dt_IOPER_DISPOSE
    , dt_EIterOper_ALLOC_MAX = dt_IOPER_DISPOSE
    
    /* Iteration Control and Data Access */
    
    , dt_IOPER_ASPECT_CONTROL = 100
    , dt_IOPER_ACTUAL     /**< TODO Documentation. @see dt_IOPER_ASPECT_CONTROL */
    , dt_IOPER_ACTUALKEYS /**< TODO Documentation. @see dt_IOPER_ASPECT_CONTROL */
    , dt_IOPER_NEXT       /**< TODO Documentation. @see dt_IOPER_ASPECT_CONTROL */
    , dt_IOPER_PREVIOUS   /**< TODO Documentation. @see dt_IOPER_ASPECT_CONTROL */
    , dt_EIterOper_CONTROL_MIN = dt_IOPER_ACTUAL
    , dt_EIterOper_CONTROL_MAX = dt_IOPER_PREVIOUS
    
    /* State Query */
    
    , dt_IOPER_ASPECT_STATE = 150
    , dt_IOPER_GETCTNR     /**< TODO Documentation. @see dt_IOPER_ASPECT_STATE */
    , dt_IOPER_GETMODE     /**< TODO Documentation. @see dt_IOPER_ASPECT_STATE */
    , dt_IOPER_HASSTARTED  /**< TODO Documentation. @see dt_IOPER_ASPECT_STATE */
    , dt_IOPER_HASNEXT     /**< TODO Documentation. @see dt_IOPER_ASPECT_STATE */
    , dt_IOPER_HASPREVIOUS /**< TODO Documentation. @see dt_IOPER_ASPECT_STATE */
    , dt_EIterOper_STATE_MIN = dt_IOPER_GETCTNR
    , dt_EIterOper_STATE_MAX = dt_IOPER_HASPREVIOUS
    
    /* Data Mutation (Destructive methods) */
    
    , dt_IOPER_ASPECT_MUTATE = 200
    , dt_IOPER_SET    /**< TODO Documentation. @see dt_IOPER_ASPECT_MUTATE */
    , dt_IOPER_REMOVE /**< TODO Documentation. @see dt_IOPER_ASPECT_MUTATE */
    , dt_EIterOper_MUTATE_MIN = dt_IOPER_SET
    , dt_EIterOper_MUTATE_MAX = dt_IOPER_REMOVE
    
    /* Utilities */
    
    , dt_IOPER_ASPECT_UTIL = 250
    , dt_IOPER_COMPARE /**< TODO Documentation. @see dt_IOPER_ASPECT_UTIL */
    , dt_EIterOper_UTIL_MIN = dt_IOPER_COMPARE
    , dt_EIterOper_UTIL_MAX = dt_IOPER_COMPARE
    
    , dt_EIterOper_MIN = dt_EIterOper_ALLOC_MIN
    , dt_EIterOper_MAX = dt_EIterOper_UTIL_MAX
};


/**
 * TODO Documentation
 */
enum dt_EStrCmpMethod_ {
    
    dt_CSTR_CMP_CMP = 1
    , dt_CSTR_CMP_COLL
    
    , dt_EStrCmpMethod_MIN = dt_CSTR_CMP_CMP
    , dt_EStrCmpMethod_MAX = dt_CSTR_CMP_COLL
};


/*##############################################################################
 * [[[   TYPE DEFINITIONS   ]]]
 */


typedef struct dt_CtnrApiArgs_    dt_CtnrApiArgs;    /**< @see dt_CtnrApiArgs_ */
typedef struct dt_IterApiArgs_    dt_IterApiArgs;    /**< @see dt_IterApiArgs_ */

typedef struct dt_CtnrAllocArgs_  dt_CtnrAllocArgs;  /**< @see dt_CtnrAllocArgs_ */
typedef struct dt_CtnrOperArgs_   dt_CtnrOperArgs;   /**< @see dt_CtnrOperArgs_ */
typedef struct dt_CtnrStateArgs_  dt_CtnrStateArgs;  /**< @see dt_CtnrStateArgs_ */
typedef struct dt_CtnrDataArgs_   dt_CtnrDataArgs;   /**< @see dt_CtnrDataArgs_ */
typedef struct dt_CtnrShiftArgs_  dt_CtnrShiftArgs;  /**< @see dt_CtnrShiftArgs_ */
typedef struct dt_CtnrIterArgs_   dt_CtnrIterArgs;   /**< @see dt_CtnrIterArgs_ */

typedef struct dt_IterAllocArgs_  dt_IterAllocArgs;  /**< @see dt_IterAllocArgs_ */
typedef struct dt_IterCtrlArgs_   dt_IterCtrlArgs;   /**< @see dt_IterCtrlArgs_ */
typedef struct dt_IterStateArgs_  dt_IterStateArgs;  /**< @see dt_IterStateArgs_ */
typedef struct dt_IterMutateArgs_ dt_IterMutateArgs; /**< @see dt_IterMutateArgs_ */
typedef struct dt_IterUtilArgs_   dt_IterUtilArgs;   /**< @see dt_IterUtilArgs_ */


/**
 * TODO Documentation
 */
typedef dt_EEcode (*dt_FCtnrApi) (dt_CtnrApi* A, dt_ECtnrOper oper, dt_CtnrApiArgs* args);


/**
 * TODO Documentation
 */
typedef dt_EEcode (*dt_FIterApi) (dt_IterApi* A, dt_EIterOper oper, dt_IterApiArgs* args);


/*##############################################################################
 * [[[   STRUCTS AND UNIONS   ]]]
 */


/**
 * The container base structure.
 * All containers must declare its first field to be of this type.
 */
struct dt_Ctnr_ {

    dt_CtnrApi* api;   /**< The container's API (or "type"). */
    dt_EEcode   ecode; /**< The current error state of the container. */
};


/**
 * The iterator base structure.
 */
struct dt_Iter_ {

    dt_IterApi* api;   /**< The iterator's API. */
    dt_EEcode   ecode; /**< The current error state of the iterator. */
};


/**
 * TODO Documentation
 */
struct dt_CtnrApi_ {
    
    /* Data */
    
    const dt_CtnrApi* base;     /**< The base API (for "subclassing"). */
    const dt_Opts*    opts;     /**< Standard container options. */
    const dt_State*   state;    /**< Global (unmodified) state for instantiated containers. */
    const char*       implname; /**< A descriptive name. */
    size_t            bytesize; /**< The size of the container, in bytes. */
    dt_ENature*       natures;  /**< A NULL-terminated list of self-declared natures. */
    
    /* Functions */
    
    dt_FCtnrApi       allocf;   /**< The mandatory container allocation and instantiation delegate. @see dt_CtnrAllocArgs_ */
    dt_FCtnrApi       operf;    /**< The mandatory container operation delegate. @see dt_CtnrOperArgs_ */
    dt_FCtnrApi       statef;   /**< The mandatory state management delegate. @see dt_CtnrStateArgs_ */
    dt_FCtnrApi       dataf;    /**< The mandatory data access delegate. @see dt_CtnrDataArgs_ */
    dt_FCtnrApi       shiftf;   /**< The optional data shift delegate. @see dt_CtnrShiftArgs_ */
    dt_FCtnrApi       iterf;    /**< The optional iterator generator delegate. @see dt_CtnrIterArgs_ */
};


/**
 * TODO Documentation
 */
struct dt_IterApi_ {
    
    /* Data */
    
    const dt_IterApi*  base;
    const char*        implname;
    size_t             bytesize;
    
    /* Functions */
    
    dt_FCtnrApi        allocf;
    dt_FCtnrApi        controlf;
    dt_FCtnrApi        statef;
    dt_FCtnrApi        mutatef;
    dt_FCtnrApi        utilf;
};


/**
 * TODO Documentation
 */
struct dt_CtnrAllocArgs_ {
    
    dt_Ctnr* ctnr;
    dt_Opts* opts;
    dt_Ctnr* ctnr_ret;
};


/**
 * TODO Documentation
 */
struct dt_CtnrOperArgs_ {
    
    dt_Ctnr* ctnr;
    size_t   amount;
};


/**
 * TODO Documentation
 */
struct dt_CtnrStateArgs_ {
    
    dt_Ctnr* ctnr;
    int      prop;
    void*    value;
    void*    voidp_ret;
};


/**
 * TODO Documentation
 */
struct dt_CtnrDataArgs_ {
    
    dt_Ctnr* ctnr;
    size_t*  sz_ret;
    void*    copyptr_ret;
    void*    key;
    void*    val;
    size_t   qty;
};


/**
 * TODO Documentation
 */
struct dt_CtnrShiftArgs_ {
    
    dt_Ctnr* ctnr;
    void*    val;
    size_t   amount;
    size_t   sz_ret;
};


/**
 * TODO Documentation
 */
struct dt_CtnrIterArgs_ {
    
    dt_Ctnr* ctnr;
    dt_Iter* iter_ret;
    void*    key;
    int      mode;
};


/**
 * TODO Documentation
 */
struct dt_CtnrApiArgs_ {
    
    dt_ECtnrOper         aspect;
    
    union {
        dt_CtnrAllocArgs alloc;
        dt_CtnrOperArgs  oper;
        dt_CtnrStateArgs state;
        dt_CtnrDataArgs  data;
        dt_CtnrShiftArgs shift;
        dt_CtnrIterArgs  iter;
    };
};


/**
 * TODO Documentation
 */
struct dt_IterAllocArgs_ {
    
    dt_Iter* iter;
};


/**
 * TODO Documentation
 */
struct dt_IterCtrlArgs_ {
    
    dt_Iter* iter;
    void*    val_ret;
};


/**
 * TODO Documentation
 */
struct dt_IterStateArgs_ {
    
    dt_Iter* iter;
    int      bool_ret;
    int      int_ret;
    dt_Ctnr* ctnr_ret;
};


/**
 * TODO Documentation
 */
struct dt_IterMutateArgs_ {
    
    dt_Iter* iter;
    void*    val;
};


/**
 * TODO Documentation
 */
struct dt_IterUtilArgs_ {
    
    dt_Iter* iter;
    dt_Iter* other;
    int      ret;
};


/**
 * TODO Documentation
 */
struct dt_IterApiArgs_ {
    
    dt_EIterOper aspect;
    
    union {
        dt_IterAllocArgs  iter;
        dt_IterCtrlArgs   ctrl;
        dt_IterStateArgs  state;
        dt_IterMutateArgs mutate;
        dt_IterUtilArgs   util;
    };
};

#endif
