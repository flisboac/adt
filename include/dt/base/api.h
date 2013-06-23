
#ifndef DT_BASE_API_H_
#define DT_BASE_API_H_


#include <stddef.h>
#include "dtcfg.h"
#include "dt/base/defs.h"


/*##############################################################################
 * [[[   EXTERNAL DATA   ]]]
 */


dt_DATA const dt_CtnrApi* const dt_vector_api;  /**< Contiguous array of values. */
#if 0
/* TBIL */

/* Containers */
dt_DATA const dt_CtnrApi* const dt_deque_api;   /**< Doubly-ended vector. */
dt_DATA const dt_CtnrApi* const dt_dlist_api;   /**< Doubly-linked list. */
dt_DATA const dt_CtnrApi* const dt_flist_api;   /**< Forward-linked list. */
dt_DATA const dt_CtnrApi* const dt_hashset_api; /**< Hash-based non-ordered set. */
dt_DATA const dt_CtnrApi* const dt_treeset_api; /**< Tree-based ordered set. */
dt_DATA const dt_CtnrApi* const dt_hashmap_api; /**< Hash-based non-ordered map. */
dt_DATA const dt_CtnrApi* const dt_treemap_api; /**< Tree-based ordered map. */
dt_DATA const dt_CtnrApi* const dt_bvector_api; /**< Bit-oriented vector. */
/* Adaptors */
dt_DATA const dt_CtnrApi* const dt_queue_api;   /**< Simple queue adaptor. */
dt_DATA const dt_CtnrApi* const dt_pqueue_api;  /**< Priority queue using comparison. */
dt_DATA const dt_CtnrApi* const dt_stack_api;   /**< Simple stack adaptor. */
dt_DATA const dt_CtnrApi* const dt_graph_api;   /**< Tree/Graph container. */
#endif

dt_DATA const dt_Type* const dt_ctnr_type;   /**< #dt_Type for #dt_Ctnr, pointer-based. */
        typedef dt_Ctnr*     dt_ctnr;        /**< Raw type's @c typedef for #dt_ctnr_type. */
        #define              dt_rCtnr(m, a)  dt_CASTCALL(dt_ctnr, m, a)
        #define              dt_rCT(m, a)    dt_rCtnr(dt_ ## m, a)
        
dt_DATA const dt_Type* const dt_iter_type;   /**< #dt_Type for #dt_Iter, pointer-based */
        typedef dt_Iter*     dt_iter;        /**< Raw type's @c typedef for #dt_iter_type. */
        #define              dt_rIter(m, a)  dt_CASTCALL(dt_iter, m, a)
        #define              dt_rIT(m, a)    dt_rIter(dt_ ## m, a)
        
dt_DATA const dt_Type* const dt_voidp_type;  /**< #dt_Type for a @c void pointer, pointer-based */
        typedef void*        dt_voidp;       /**< Raw type's @c typedef for #dt_voidp_type. */
        #define              dt_rVoidp(m, a) dt_CASTCALL(dt_voidp, m, a)
        #define              dt_rVP(m, a)    dt_rVoidp(dt_ ## m, a)
        
dt_DATA const dt_Type* const dt_cstr_type;   /**< #dt_Type for a standard C string, pointer-based */
        typedef char*        dt_cstr;        /**< Raw type's @c typedef for #dt_cstr_type. */
        #define              dt_rCstr(m, a)  dt_CASTCALL(dt_cstr, m, a)
        #define              dt_rCS(m, a)    dt_rVoidp(dt_ ## m, a)
        
dt_DATA const dt_Type* const dt_sz_type;     /**< #dt_Type for @c size_t, value-based */
        typedef size_t       dt_sz;          /**< Raw type's @c typedef for #dt_sz_type. */
        #define              dt_rSz(m, a)    dt_DCASTCALL(dt_sz*, m, a)
        #define              dt_rSZ(m, a)    dt_rSz(dt_ ## m, a)

#if 0
/* TBIL */
dt_DATA const dt_Type* const dt_mbstr_type;   /* Pointer-based */
        typedef char*        dt_mbstr;
dt_DATA const dt_Type* const dt_wstr_type;    /* Pointer-based */
        typedef wchar_t*     dt_wstr;
dt_DATA const dt_Type* const dt_char_type;    /* Value-based */
        typedef char         dt_char;
dt_DATA const dt_Type* const dt_int_type;     /* Value-based */
        typedef int          dt_int;
dt_DATA const dt_Type* const dt_long_type;    /* Value-based */
        typedef long         dt_long;
dt_DATA const dt_Type* const dt_float_type;   /* Value-based */
        typedef float        dt_float;
dt_DATA const dt_Type* const dt_double_type;  /* Value-based */
        typedef double       dt_double;
#endif


/*##############################################################################
 * [[[   BASIC CONTAINER API   ]]]
 */


/* Allocation */
dt_API dt_Ctnr* dt_create(const dt_CtnrApi* type);
dt_API dt_Ctnr* dt_createfor(const dt_CtnrApi* type, const dt_Type* vtype, const dt_Type* ktype);
dt_API dt_Ctnr* dt_createwith(const dt_CtnrApi* type, dt_Opts* opts);
dt_API dt_EEcode dt_initwith(dt_Ctnr* C, dt_Opts* opts);
dt_API dt_EEcode dt_finalize(dt_Ctnr* C);
dt_API dt_EEcode dt_dispose(dt_Ctnr* C);
dt_API dt_EEcode dt_swap(dt_Ctnr *C, dt_Ctnr *O);
dt_API dt_Ctnr* dt_dup(dt_Ctnr* C);

/* State */
dt_API dt_EEcode dt_getecode(dt_Ctnr* C);
dt_API dt_State* dt_getstate(dt_Ctnr* C, dt_State* S);
dt_API dt_EEcode dt_setstate(dt_Ctnr* C, dt_State* S);
dt_API dt_EEcode dt_getprop(dt_Ctnr* C, int prop, void* val);
dt_API dt_EEcode dt_setprop(dt_Ctnr* C, int prop, void* val);
dt_API size_t dt_getlen(dt_Ctnr* C);
dt_API size_t dt_getcap(dt_Ctnr* C);

/* Data */
dt_API size_t dt_has(dt_Ctnr* C, ... /* k */);
dt_API void* dt_get(dt_Ctnr* C, ... /* k */);
dt_API dt_EEcode dt_put(dt_Ctnr* C, ... /* p, k */);
dt_API dt_EEcode dt_set(dt_Ctnr* C, ... /* p, v, k */);
dt_API dt_EEcode dt_insert(dt_Ctnr* C, ... /* v, k */);
dt_API dt_EEcode dt_remove(dt_Ctnr* C, ... /* p, k */);
dt_API dt_EEcode dt_flip(dt_Ctnr* C, ... /* p, k */);
dt_API dt_EEcode dt_reset(dt_Ctnr*C, ... /* p, k */);
dt_API size_t dt_removec(dt_Ctnr* C, size_t amount, ... /* k */);

/* Bit data */
dt_API int dt_bittest(dt_Ctnr* C, size_t k);
dt_API int dt_biton(dt_Ctnr* C, size_t k);
dt_API int dt_bitoff(dt_Ctnr* C, size_t k);
dt_API int dt_bitflip(dt_Ctnr* C, size_t k);
dt_API int dt_bitreset(dt_Ctnr* C, size_t k);
dt_API size_t dt_bitcount(dt_Ctnr* C);

/* Shift */
dt_API dt_EEcode dt_push(dt_Ctnr* C, ... /* v */);
dt_API dt_EEcode dt_pushi(dt_Ctnr* C, ... /* v */);
dt_API void* dt_pop(dt_Ctnr* C, ... /* *v */);
dt_API void* dt_popi(dt_Ctnr* C, ... /* *v */);
#define dt_pushl dt_pushi
#define dt_pushr dt_push
#define dt_popl dt_popi
#define dt_popr dt_pop
dt_API size_t dt_rot(dt_Ctnr* C, size_t count);
dt_API size_t dt_roti(dt_Ctnr* C, size_t count);
dt_API size_t dt_crot(dt_Ctnr* C, size_t count);
dt_API size_t dt_croti(dt_Ctnr* C, size_t count);
#define dt_rotl dt_roti
#define dt_rotr dt_rot
#define dt_crotl dt_croti
#define dt_crotr dt_crot

/* Operations */
dt_API dt_EEcode dt_sort(dt_Ctnr *C, int reverse);
dt_API dt_EEcode dt_reverse(dt_Ctnr* C);
dt_API dt_EEcode dt_reserve(dt_Ctnr *C, size_t size);
dt_API dt_EEcode dt_resize(dt_Ctnr *C, size_t size);
dt_API dt_EEcode dt_rehash(dt_Ctnr* C);
dt_API dt_EEcode dt_zip(dt_Ctnr* C);
dt_API dt_EEcode dt_clear(dt_Ctnr *C);


/*##############################################################################
 * [[[   ITERATORS API   ]]]
 */


dt_API dt_Iter* dt_iterate(dt_Ctnr *C, int mode);
dt_API dt_Iter* dt_iterateat(dt_Ctnr *C, int mode, ... /* k */);

dt_API dt_Ctnr* dt_igetctnr(dt_Iter* I);
dt_API dt_EEcode dt_idispose(dt_Iter* I);
dt_API void* dt_iactual(dt_Iter* I);
dt_API void* dt_ikeys(dt_Iter* I);
dt_API void* dt_inext(dt_Iter* I);
dt_API void* dt_iprev(dt_Iter* I);
dt_API int dt_istarted(dt_Iter* I);
dt_API int dt_ihasnext(dt_Iter* I);
dt_API int dt_ihasprev(dt_Iter* I);
dt_API dt_EEcode dt_iset(dt_Iter* I, ... /* v */);
dt_API dt_EEcode dt_iremove(dt_Iter* I);
dt_API int dt_icompare(dt_Iter* I, dt_Iter* O);


/*##############################################################################
 * [[[   ALGORITHMS API   ]]]
 */


dt_API size_t dt_hash(dt_Ctnr *C);
dt_API int dt_compare(dt_Ctnr* C1, dt_Ctnr* C2);

dt_API dt_Ctnr* dt_union(dt_Ctnr* C1, dt_Ctnr* C2, dt_Ctnr* O);
dt_API dt_Ctnr* dt_diff(dt_Ctnr* C1, dt_Ctnr* C2, dt_Ctnr* O);
dt_API dt_Ctnr* dt_symdiff(dt_Ctnr* C1, dt_Ctnr* C2, dt_Ctnr* O);
dt_API dt_Ctnr* dt_inters(dt_Ctnr* C1, dt_Ctnr* C2, dt_Ctnr* O);

dt_API dt_Ctnr* dt_keys(dt_Ctnr *C, dt_Ctnr* O);
dt_API dt_Ctnr* dt_values(dt_Ctnr *C, dt_Ctnr* O);
dt_API dt_Ctnr* dt_head(dt_Ctnr *C, dt_Ctnr* O);
dt_API dt_Ctnr* dt_tail(dt_Ctnr *C, dt_Ctnr* O);
dt_API dt_Ctnr* dt_range(dt_Iter* from, dt_Iter* to, dt_Ctnr* O);
dt_API void* dt_index(dt_Ctnr* C, ... /* k */);
dt_API void* dt_first(dt_Ctnr* C);
dt_API void* dt_last(dt_Ctnr* C);


/*##############################################################################
 * [[[   API API (for the lack of names...)   ]]]
 */


dt_API int dt_isvalidtype(const dt_Type* T);
dt_API int dt_isvalidctnrapi(const dt_CtnrApi* C);
dt_API int dt_isvaliditerapi(const dt_IterApi* I);
dt_API const dt_Type* dt_isbasetype(const dt_Type* T, const dt_Type* base);
dt_API const dt_CtnrApi* dt_isbasectnrapi(const dt_CtnrApi* C, const dt_CtnrApi* base);
dt_API const dt_IterApi* dt_isbaseiterapi(const dt_IterApi* I, const dt_IterApi* base);

dt_API const char* dt_Type_getname(const dt_Type* T, dt_Type** which);
dt_API dt_ERawType dt_Type_getrawtype(const dt_Type* T, dt_Type** which);
dt_API dt_FHash dt_Type_gethashf(const dt_Type* T, dt_Type** which);
dt_API dt_FCmp dt_Type_getcmpf(const dt_Type* T, dt_Type** which);
dt_API dt_FValue dt_Type_getvaluef(const dt_Type* T, void** valuep, dt_Type** which);
dt_API size_t dt_Type_getsize(const dt_Type* T, dt_Type** which);


/*##############################################################################
 * [[[   UTILITY API   ]]]
 */


dt_API dt_Type* dt_newarray(const dt_Type* base, size_t size);
dt_API dt_Type* dt_initarray(const dt_Type* base, size_t size);
dt_API void dt_disposearray(dt_Type* T);

dt_API dt_Opts* dt_clearopts(dt_Opts* O);
dt_API dt_Opts* dt_defaultopts(dt_Opts* O);
dt_API dt_Opts* dt_defaultoptsfor(dt_CtnrApi* type, dt_Opts* opts);
dt_API dt_State* dt_clearstate(dt_State* S);
dt_API dt_State* dt_defaultstate(dt_State* O);
dt_API dt_State* dt_defaultstatefor(dt_CtnrApi* type, dt_State* state);

dt_API dt_Type* dt_copytype(dt_Type* to, dt_Type* from);
dt_API dt_Opts* dt_copyopts(dt_Opts* to, dt_Opts* from);
dt_API dt_State* dt_copystate(dt_State* to, dt_State* from);
dt_API size_t dt_hashcstr(const char* s, size_t sz);
dt_API size_t dt_hashval(const dt_Type* T, const void* o);



#endif
