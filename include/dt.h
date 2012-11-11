/**
 * @file include/dt.h
 */

#ifndef DT_H_
#define DT_H_

#include <stddef.h>

/*##############################################################################
 * [[[   CONFIGURATION   ]]]
 */


#define dt_NAME "dt"/*@@APPNAME@@*/
#define dt_RELEASETYPE "beta"/*@@RELEASETYPE@@*/
#define dt_MAJORVERSION (0)/*@@MAJORVERSION@@*/
#define dt_MINORVERSION (1)/*@@MINORVERSION@@*/
#define dt_PATCHVERSION (0)/*@@PATCHVERSION@@*/



/*##############################################################################
 * [[[   DEFINES   ]]]
 */


#define dt_STRQT(s) #s
#define dt_STRFY(s) um_STRQT(s)
#define dt_NOSIZE ((size_t)-1)
#define dt_NOCMP (-2)
#define dt_EEcode_isvalid(t) (t > dt_OK && (t) < dt_ERRMAX)
#define dt_EIterMode_isvalid(t) (t > dt_ITER_NONE && (t) < dt_ITER_MAX)
#define dt_ENature_isvalid(t) (t > dt_NAT_NONE && (t) < dt_NAT_MAX)

/** The release name. Do not change! */
#define dt_RELEASENAME dt_NAME \
	" " dt_STRFY(dt_MAJORVERSION) \
	"." dt_STRFY(dt_MINORVERSION) \
	"." dt_STRFY(dt_PATCHVERSION) \
	"-" dt_RELEASETYPE

#ifndef BUILDINGDOCS
#if !defined(dt_STATIC) && defined(_WIN32)
#   define dt_FIMPORT __declspec(dllimport)
#   define dt_FEXPORT __declspec(dllexport)
#   define dt_DIMPORT dt_FIMPORT
#   define dt_DEXPORT dt_FEXPORT
#else
#   define dt_FIMPORT extern
#   define dt_FEXPORT
#   define dt_DIMPORT dt_FIMPORT
#   define dt_DEXPORT
#endif


#if defined(dt_BUILDING)
#   define dt_API dt_FEXPORT
#   define dt_DATA dt_DEXPORT
#   if defined(dt_STATIC)
#       define dt_IAPI static
#       define dt_IDATA
#   else
#       if defined(__GNUC__) && ((__GNUC__*100 + __GNUC_MINOR__) >= 302) && \
                defined(__ELF__)
#           define dt_IAPI __attribute__((visibility("hidden"))) extern
#           define dt_IDATA dt_IAPI
#       else
#           define dt_IAPI extern
#           define dt_IDATA extern
#       endif
#   endif
#else
#   define dt_API dt_FIMPORT
#   define dt_DATA dt_DIMPORT
#endif
#else

#define dt_FIMPORT /**< Target-dependent marker for symbols to be exported to shared libraries. */
#define dt_FEXPORT /**< Target-dependent marker for symbols to be imported from shared libraries. */
#define dt_API     /**< Target-dependent marker for external library functions. */
#define dt_DATA    /**< Target-dependent marker for external library variables. */
#define dt_IAPI    /**< Target-dependent marker for internal library functions. */
#define dt_IDATA   /**< Target-dependent marker for internal library variables. */

#endif

/*##############################################################################
 * [[[   ENUMERATIONS   ]]]
 */

typedef enum dt_EEcode_ dt_EEcode;       /**< @see dt_EEcode_ */
typedef enum dt_EIterMode_ dt_EIterMode; /**< @see dt_EIterMode_ */
typedef enum dt_ENature_ dt_ENature;     /**< @see dt_ENature_ */
typedef enum dt_EValueAct_ dt_EValueAct; /**< @see dt_EValueAct_ */

/**
 * Represents an error or exit code.
 *
 * Generally, values greater than @c dt_OK are considered to be error
 * conditions, while values less than @c dt_OK are considered to be warning
 * or informational conditions.
 */
enum dt_EEcode_ {

      dt_OK = 0  /**< Operation successful. */
    , dt_ERROR   /**< An error ocurred. */
    , dt_ERRNULL /**< Null pointer passed (somewhere). */
    , dt_ERRIMPL /**< Not implemented. */
    , dt_ERRSUPP /**< Not supported. */
    , dt_ERRMEM  /**< Out of memory. */
    , dt_ERRINIT /**< Error while initializing or finalizing values. */
    , dt_ERRMISS /**< Invalid or missing arguments or operands. */

    /* ... */

    , dt_ERRMAX  /**< Placeholder, for the maximum error code value. */
    , dt_ERRMIN = dt_OK
};


/**
 *
 */
enum dt_EIterMode_ {

      dt_ITER_NONE = 0  /**< Invalid iterator or iteration mode. */
    , dt_ITER_ORDER     /**< Iterates in normal order (generally left-right). */
    , dt_ITER_RORDER    /**< Iterates in reverse order. */
    , dt_ITER_LEVEL     /**< Iterates in normal order, respecting levels. */
    , dt_ITER_RLEVEL    /**< Iterates in reverse order, respecting levels. */

    /** ... */

    , dt_ITER_MAX       /**< Placeholder, for the maximum iteration mode value. */
    , dt_ITER_MIN = dt_ITER_NONE
};


/**
 * Enumeration of all natures that can be assigned to containers.
 */
enum dt_ENature_ {

	  dt_NAT_NONE
	, dt_NAT_LIST    /**< Insertion-ordered sequence of values. */
	, dt_NAT_SET     /**< Group of unique values. */
	, dt_NAT_MAP     /**< Mapping from values to other values. */
	, dt_NAT_HASH    /**< Hash-based implementation. */
	, dt_NAT_BAG     /**< Values can occur more than once, while keeping uniqueness. */
	, dt_NAT_FLAT    /**< Values are held on a flat memory array. */
	, dt_NAT_MATRIX  /**< Indexes with more than just one key. */
	, dt_NAT_ADAPTOR /**< Front-end for another container. */
	, dt_NAT_ORDERED /**< Values are automatically ordered. */

	/* ... */

	, dt_NAT_MAX
	, dt_NAT_MIN = dt_NAT_LIST
} ;


/**
 * Enumeration of all possible actions on container keys or values.
 */
enum dt_EValueAct_ {

	  dt_VAL_NONE = 0
	, dt_VAL_INIT
	, dt_VAL_QUIT
	, dt_VAL_COPY
	, dt_VAL_MAX
};


/*##############################################################################
 * [[[   TYPE DEFINITIONS   ]]]
 */


typedef struct dt_Type_ dt_Type;
typedef struct dt_Ctnr_ dt_Ctnr;
typedef struct dt_Iter_ dt_Iter;
typedef struct dt_Opts_ dt_Opts;

typedef struct dt_CtnrApi_ dt_CtnrApi;
typedef struct dt_IterApi_ dt_IterApi;

typedef size_t (*dt_FHash)(dt_Type* T, void* a);
typedef int (*dt_FCmp)(dt_Type* T, void *a, void* b);
typedef dt_EEcode (*dt_FValue)(void* vinitp, dt_EValueAct act, dt_Type* T, void* obj, size_t obj_count, void* to);
typedef int (*dt_FEvent)(void* eventp, dt_EEcode ecode, dt_Ctnr* C, void* o, size_t count, int isval);
typedef void* (*dt_FAlloc)(void* allocp, void* o, size_t bytesz, size_t align);


/*##############################################################################
 * [[[   STRUCTS AND UNIONS   ]]]
 */


/**
 *
 */
struct dt_Type_ {

	const dt_Type* base;
	const char* name; /**< A descriptive name for the type. */
	size_t vsize;     /**< Vector size for the type.
	                       Must be 1 for scalar types, 0 for undefined size. */
	size_t esize;     /**< Element size of the type, in bytes.
	                       Must be greater than 0. */
	dt_FCmp cmpf;     /**< The comparison function. @see dt_FCmp */
	dt_FHash hashf;   /**< The hashing function. @see dt_FHash */
	dt_FValue vinitf; /**< Initializer/finalizer for keys or values. */
	void* vinitp;     /**< Optional state for @c vinitf. */
};


/**
 *
 */
struct dt_Opts_ {

	/* Types */
	dt_Type* ktype;
	dt_Type* vtype;

	/* Data */
	size_t cap;
	size_t malign;
	size_t len;    /**< Container's actual length, in elements. */
	size_t capmult;
	size_t load;

	/* State */
	dt_EEcode ecode;
	int immutable; /**< If 1, the container cannot change its values.
	                   It can still reserve memory space, though. */
	int frozen;    /**< If 1, the container cannot grow or shrink (in terms of
	                    memory space). It can still change its values, though.*/
	int autoord;   /**< If 1, automatically orders elements on insertion. */
	void* defv;    /**< The default value. */

	/* Functions */
	dt_FAlloc allocf;
	void* allocp;
	dt_FEvent eventf;
	void* eventp;
};


/**
 *
 */
struct dt_Ctnr_ {

	dt_CtnrApi *api;
	dt_EEcode ecode;
};


/**
 *
 */
struct dt_Iter_ {

	dt_IterApi *api;
	dt_Ctnr *C;
	dt_EEcode ecode;
};


/**
 *
 */
struct dt_CtnrApi_ {

	/*
	 * Implementation details.
	 */

	const dt_CtnrApi* base;
	const char* (*getimplname)(dt_CtnrApi* A);
	size_t (*getbytesize)(dt_CtnrApi* A);
	const dt_ENature* (*getnatures)(dt_CtnrApi* A);

	/*
	 * Creation and disposal.
	 */

	dt_Ctnr* (*createwith)(dt_CtnrApi* A, dt_Opts *opts);
	dt_Ctnr* (*initwith)(dt_CtnrApi* A, dt_Ctnr* C, dt_Opts *opts);
	dt_EEcode (*dispose)(dt_CtnrApi* A, dt_Ctnr* C);
	dt_Ctnr* (*copy)(dt_CtnrApi* A, dt_Ctnr* C);

	/*
	 * State.
	 */

	dt_Opts* (*defaultopts)(dt_CtnrApi* A, dt_Opts* opts);
	dt_Opts* (*getopts)(dt_CtnrApi* A, dt_Ctnr* C, dt_Opts* opts);
	dt_EEcode (*setopts)(dt_CtnrApi* A, dt_Ctnr* C, dt_Opts* opts);

	/*
	 * Essential data access api.
	 */

	size_t (*has)(dt_CtnrApi* A, dt_Ctnr* C, void* k);
	void* (*get)(dt_CtnrApi* A, dt_Ctnr* C, void* k);
	dt_EEcode (*put)(dt_CtnrApi* A, dt_Ctnr* C, void* k);
	void* (*set)(dt_CtnrApi* A, dt_Ctnr* C, void* k, void* v);
	void* (*insert)(dt_CtnrApi* A, dt_Ctnr* C, void* k, void* v);
	void* (*remove)(dt_CtnrApi* A, dt_Ctnr* C, void* k);
	size_t (*removec)(dt_CtnrApi* A, dt_Ctnr* C, void* k, size_t amount);

	/*
	 * Optional data access api.
	 */

	dt_EEcode (*push)(dt_CtnrApi* A, dt_Ctnr* C, void* v);
	dt_EEcode (*pushr)(dt_CtnrApi* A, dt_Ctnr* C, void* v);
	void* (*pop)(dt_CtnrApi* A, dt_Ctnr* C);
	void* (*popr)(dt_CtnrApi* A, dt_Ctnr* C);

	size_t (*rot)(dt_CtnrApi* A, dt_Ctnr* C, size_t count);
	size_t (*rotr)(dt_CtnrApi* A, dt_Ctnr* C, size_t count);
	size_t (*crot)(dt_CtnrApi* A, dt_Ctnr* C, size_t count);
	size_t (*crotr)(dt_CtnrApi* A, dt_Ctnr* C, size_t count);

	/*
	 * Operations
	 */

    dt_EEcode (*sort)(dt_CtnrApi* A, dt_Ctnr *C, int reverse);
    dt_EEcode (*reserve)(dt_CtnrApi* A, dt_Ctnr *C, size_t size);
    dt_EEcode (*resize)(dt_CtnrApi* A, dt_Ctnr *C, size_t size);
    dt_EEcode (*swap)(dt_CtnrApi* A, dt_Ctnr *C, dt_Ctnr *O);
    dt_EEcode (*rehash)(dt_CtnrApi* A, dt_Ctnr* C);
    dt_EEcode (*clear)(dt_CtnrApi* A, dt_Ctnr *C);

    /*
     * Iterators.
     */

    dt_Iter* (*iterate)(dt_CtnrApi* A, dt_Ctnr *C, dt_EIterMode mode);
    dt_Iter* (*iterateat)(dt_CtnrApi* A, dt_Ctnr *C, dt_EIterMode mode, void* k);
};


/**
 *
 */
struct dt_IterApi_ {

	/*
	 * Implementation details.
	 */

	const dt_IterApi* base;
	size_t (*getbytesize)(dt_IterApi* A);
	const char* (*getctnrapi)(dt_IterApi* A);

    /*
     * Iteration disposal.
     */
    dt_EEcode (*dispose)(dt_IterApi* A, dt_Iter* I);

    /*
     * Iteration control.
     */

    void* (*actual)(dt_IterApi* A, dt_Iter* I);
    void* (*actualkeys)(dt_IterApi* A, dt_Iter* I);
    void* (*next)(dt_IterApi* A, dt_Iter* I);
    void* (*previous)(dt_IterApi* A, dt_Iter* I);

    /*
     * Iteration state.
     */

    dt_EIterMode (*getmode)(dt_IterApi* A, dt_Iter* I);
    int (*hasstarted)(dt_IterApi* A, dt_Iter* I);
    int (*hasnext)(dt_IterApi* A, dt_Iter* I);
    int (*hasprevious)(dt_IterApi* A, dt_Iter* I);

    /*
     * Value control.
     * These operations take place in the actual key being iterated.
     */

    dt_EEcode (*set)(dt_IterApi* A, dt_Iter* I, void* v);
    dt_EEcode (*remove)(dt_IterApi* A, dt_Iter* I);

    /*
     * Iterator (position-related) comparison
     */

    int (*compare)(dt_IterApi* A, dt_Iter* I, dt_Iter* O);
};


/*##############################################################################
 * [[[   EXTERNAL DATA   ]]]
 */


dt_DATA const dt_CtnrApi* const dt_vector_api;
#if 0
dt_DATA const dt_CtnrApi* const dt_deque_api;
dt_DATA const dt_CtnrApi* const dt_hashset_api;
dt_DATA const dt_CtnrApi* const dt_ordset_api;
dt_DATA const dt_CtnrApi* const dt_hashmap_api;
dt_DATA const dt_CtnrApi* const dt_ordmap_api;
dt_DATA const dt_CtnrApi* const dt_queue_api;
dt_DATA const dt_CtnrApi* const dt_stack_api;
#endif

dt_DATA const dt_Type dt_cstr_type;
dt_DATA const dt_Type dt_wstr_type;
dt_DATA const dt_Type dt_int_type;
dt_DATA const dt_Type dt_long_type;
dt_DATA const dt_Type dt_flt_type;
dt_DATA const dt_Type dt_dbl_type;
dt_DATA const dt_Type dt_voidp_type;
dt_DATA const dt_Type dt_sz_type;


/*##############################################################################
 * [[[   UTILITY API   ]]]
 */


dt_API dt_Opts* dt_clearopts(dt_Opts* O);
dt_API dt_Opts* dt_defaultopts(dt_Opts* O);
dt_API dt_Opts* dt_defaultoptsfor(dt_CtnrApi* type, dt_Opts* opts);
dt_API dt_Type* dt_copytype(dt_Type* T, dt_Type* O);
dt_API dt_Opts* dt_copyopts(dt_Opts* T, dt_Opts* O);
dt_API size_t dt_hashstring(const char* s);

#define dt_Type_size(T) ((T) ? (T)->esize * ((T)->vsize > 0 ? (T)->vsize : 1))
dt_API int dt_Type_hashash(dt_Type* T);
dt_API int dt_Type_hascmp(dt_Type* T);
dt_API int dt_Type_hasvinit(dt_Type* T);
dt_API size_t dt_Type_hash(dt_Type* T, void* o);
dt_API int dt_Type_cmp(dt_Type* T, void *a, void* b);
dt_API int dt_Type_vinit(dt_Type* T, int finalize, void* o, size_t count);


/*##############################################################################
 * [[[   BASIC CONTAINER API   ]]]
 */


dt_API dt_Ctnr* dt_create(dt_CtnrApi* type);
dt_API dt_Ctnr* dt_createfor(dt_CtnrApi* type, dt_Type* vtype, dt_Type* ktype);
dt_API dt_Ctnr* dt_createwith(dt_CtnrApi type, dt_Opts* opts);
dt_API dt_EEcode dt_dispose(dt_Ctnr* C);
dt_API dt_Ctnr* dt_copy(dt_Ctnr* C);

dt_API dt_Opts* dt_getopts(dt_Ctnr* C, dt_Opts* S);
dt_API dt_EEcode dt_setopts(dt_Ctnr* C, dt_Opts* S);
dt_API dt_EEcode dt_getecode(dt_Ctnr* C);
dt_API size_t dt_getlen(dt_Ctnr* C);
dt_API size_t dt_getcap(dt_Ctnr* C);
dt_API const dt_ENature* dt_getnatures(dt_Ctnr* C);
dt_API int dt_isnature(dt_Ctnr* C, dt_ENature nature);

dt_API size_t dt_has(dt_Ctnr* C, void* k);
dt_API void* dt_get(dt_Ctnr* C, void* k);
dt_API dt_EEcode dt_put(dt_Ctnr* C, void* k);
dt_API void* dt_set(dt_Ctnr* C, void* k, void* v);
dt_API void* dt_insert(dt_Ctnr* C, void* k, void* v);
dt_API void* dt_remove(dt_Ctnr* C, void* k);
dt_API size_t dt_removec(dt_Ctnr* C, void* k, size_t amount);

dt_API dt_EEcode dt_push(dt_Ctnr* C, void* v);
dt_API dt_EEcode dt_pushr(dt_Ctnr* C, void* v);
dt_API void* dt_pop(dt_Ctnr* C);
dt_API void* dt_popr(dt_Ctnr* C);

dt_API size_t dt_rot(dt_Ctnr* C, size_t count);
dt_API size_t dt_rotr(dt_Ctnr* C, size_t count);
dt_API size_t dt_crot(dt_Ctnr* C, size_t count);
dt_API size_t dt_crotr(dt_Ctnr* C, size_t count);

dt_API dt_EEcode dt_sort(dt_Ctnr *C, int reverse);
dt_API dt_EEcode dt_reserve(dt_Ctnr *C, size_t size);
dt_API dt_EEcode dt_resize(dt_Ctnr *C, size_t size);
dt_API dt_EEcode dt_swap(dt_Ctnr *C, dt_Ctnr *O);
dt_API dt_EEcode dt_rehash(dt_Ctnr* C);
dt_API dt_EEcode dt_clear(dt_Ctnr *C);


/*##############################################################################
 * [[[   ITERATORS API   ]]]
 */


dt_API dt_Iter* dt_iterate(dt_Ctnr *C, dt_EIterMode mode);
dt_API dt_Iter* dt_iterateat(dt_Ctnr *C, dt_EIterMode mode, void* k);

dt_API dt_EEcode dt_idispose(dt_Iter* I);
dt_API void* dt_iactual(dt_Iter* I);
dt_API void* dt_ikeys(dt_Iter* I);
dt_API void* dt_inext(dt_Iter* I);
dt_API void* dt_iprev(dt_Iter* I);
dt_API int dt_istarted(dt_Iter* I);
dt_API int dt_ihasnext(dt_Iter* I);
dt_API int dt_ihasprev(dt_Iter* I);
dt_API dt_EEcode dt_iset(dt_Iter* I, void* v);
dt_API dt_EEcode dt_iremove(dt_Iter* I);
dt_API int dt_icompare(dt_Iter* I, dt_Iter* O);


/*##############################################################################
 * [[[   ALGORITHMS API   ]]]
 */


dt_API int dt_compare(dt_Ctnr* C1, dt_Ctnr* C2);

dt_API dt_Ctnr* dt_union(dt_Ctnr* C1, dt_Ctnr* C2, dt_Ctnr* O);
dt_API dt_Ctnr* dt_diff(dt_Ctnr* C1, dt_Ctnr* C2, dt_Ctnr* O);
dt_API dt_Ctnr* dt_symdiff(dt_Ctnr* C1, dt_Ctnr* C2, dt_Ctnr* O);
dt_API dt_Ctnr* dt_intersection(dt_Ctnr* C1, dt_Ctnr* C2, dt_Ctnr* O);

dt_API dt_Ctnr* dt_keys(dt_Ctnr *C, dt_Ctnr* O);
dt_API dt_Ctnr* dt_values(dt_Ctnr *C, dt_Ctnr* O);
dt_API dt_Ctnr* dt_head(dt_Ctnr *C, dt_Ctnr* O);
dt_API dt_Ctnr* dt_tail(dt_Ctnr *C, dt_Ctnr* O);
dt_API dt_Ctnr* dt_range(dt_Iter* from, dt_Iter* to, dt_Ctnr* O);
dt_API void* dt_first(dt_Ctnr* C);
dt_API void* dt_last(dt_Ctnr* C);

dt_API dt_Ctnr* dt_clone(dt_Ctnr* C, dt_Ctnr* O);

#endif /* DT_H_ */
