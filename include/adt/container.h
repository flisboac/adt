#ifndef ADT_BASE_H_
#define ADT_BASE_H_

#include "adtdefs.h"
#include "adt/types.h"

/*
 * [ N E W ] ===================================================================
 * Container creation
 */

adt_API adt_Container *adt_new(adt_EType ctype, ...);
adt_API adt_Container *adt_newwith(adt_Options *options);
adt_API void adt_free(adt_Container *C);
adt_API adt_Container *adt_copy(adt_Container *C);

/*
 * [ A C C E S S ] =============================================================
 * Container data access
 */

/* Has */
adt_API size_t adt_has(adt_Container *C, ...);
adt_API size_t adt_hasvalue(adt_Container *C, ...);

/* Get */
adt_API adt_Value adt_get(adt_Container *C, ...);
adt_API adt_Value adt_ocurrences(adt_Container *C, ...);
adt_API adt_Value adt_getfirst(adt_Container *C);
adt_API adt_Value adt_getlast(adt_Container *C);
#define adt_gettop adt_getfirst
#define adt_getfront adt_getfirst
#define adt_getbottom adt_getlast
#define adt_getback adt_getlast

/* Set */
adt_API adt_Value adt_set(adt_Container *C, ...);

/* Push */
adt_API adt_EEcode adt_push(adt_Container *C, ...);
adt_API adt_EEcode adt_pushl(adt_Container *C, ...);
adt_API adt_EEcode adt_pushr(adt_Container *C, ...);
adt_API adt_Value adt_pop(adt_Container *C);
adt_API adt_Value adt_popl(adt_Container *C);
adt_API adt_Value adt_popr(adt_Container *C);

/* Insertion */
adt_API adt_EEcode adt_insert(adt_Container *C, ...);
adt_API adt_Value adt_remove(adt_Container *C, ...);
adt_API adt_Value adt_removeall(adt_Container *C, ...);

/* Indexof */
adt_API adt_Value adt_index(adt_Container *C, ...);
adt_API adt_Value adt_rindex(adt_Container *C, ...);

/* Shifts */
adt_API adt_EEcode adt_rotl(adt_Container *C, size_t count); /* Fills with default */
adt_API adt_EEcode adt_rotr(adt_Container *C, size_t count);
adt_API adt_EEcode adt_crotl(adt_Container *C, size_t count); /* Circular shift */
adt_API adt_EEcode adt_crotr(adt_Container *C, size_t count);

/*
 * [ A C T I O N ] =============================================================
 * Container actions and operations
 */

adt_API adt_EEcode adt_sort(adt_Container *C);
adt_API adt_EEcode adt_resize(adt_Container *C, ...);
adt_API adt_EEcode adt_reserve(adt_Container *C, ...);
adt_API adt_EEcode adt_swap(adt_Container *C, adt_Container *O);
adt_API adt_EEcode adt_rehash(adt_Container *C);
adt_API adt_EEcode adt_clear(adt_Container *C);

/*
 * [ S T A T E ] ===============================================================
 * Container state
 */

adt_API void adt_getoptions(adt_Container *C, adt_Options *to);
adt_API adt_EEcode adt_getecode(adt_Container *C);
adt_API size_t adt_getlen(adt_Container *C);
adt_API size_t adt_getcap(adt_Container *C);
adt_API size_t adt_getcount(adt_Container *C);
adt_API adt_Value adt_getkeytype(adt_Container *C);
adt_API adt_Value adt_getvaluetype(adt_Container *C);
adt_API adt_Value adt_getdefault(adt_Container *C);
adt_API adt_ECategory[] adt_getcategories(adt_Container *C);

adt_API int adt_canreserve(adt_Container *C);
adt_API int adt_canresize(adt_Container *C);
adt_API int adt_canchange(adt_Container *C);
adt_API int adt_isempty(adt_Container *C);
adt_API int adt_isautofree(adt_Container *C);
adt_API int adt_isautoorder(adt_Container *C);

adt_API adt_Value adt_setdefault(adt_Container *C);
adt_API adt_EEcode adt_setimmutable(adt_Container *C);
adt_API int adt_setresizemult(adt_Container *C, size_t mult);
adt_API adt_EEcode adt_setautofree(adt_Container *C, int flag);
adt_API adt_EEcode adt_setautoorder(adt_Container *C, int flag);
adt_API adt_EEcode adt_sethashf(adt_Container *C, adt_FHash hashf);
adt_API adt_EEcode adt_setfinalizerf(adt_Container *C, adt_FFinalize finalizef);
adt_API adt_EEcode adt_setcomparef(adt_Container *C, adt_FCompare hashf);

/*
 * [ I T E R A T O R S ] =======================================================
 * Iterators
 */

adt_API adt_Iterator* adt_iterator(adt_Container *C, adt_EIteratorMode mode, int autofree);
adt_API adt_Iterator* adt_iteratorat(adt_Container *C, adt_EIteratorMode mode, int autofree, ...);

adt_API adt_EEcode adt_Iterator_setfn(adt_Iterator *I, adt_FIterate fn, void* state);
adt_API adt_Value adt_Iterator_actual(adt_Iterator *I);
adt_API adt_Value adt_Iterator_next(adt_Iterator *I);
adt_API adt_Value adt_Iterator_previous(adt_Iterator *I);
adt_API int adt_Iterator_hasstarted(adt_Iterator *I);
adt_API int adt_Iterator_hasnext(adt_Iterator *I);
adt_API int adt_Iterator_hasprevious(adt_Iterator *I);
adt_API adt_EIteratorMode adt_Iterator_getmode(adt_Iterator *I);
adt_API adt_ECmpResult adt_Iterator_compare(adt_Iterator *I, adt_Iterator *O);
adt_API adt_Container* adt_Iterator_getcontainer(adt_Iterator *I);
adt_API adt_Value adt_Iterator_getvalue(adt_Iterator *I);
adt_API adt_EEcode adt_Iterator_getecode(adt_Iterator *I);
adt_API adt_EEcode adt_Iterator_remove(adt_Iterator *I);
adt_API adt_EEcode adt_Iterator_setvalue(adt_Iterator *I, adt_Value val);
adt_API void adt_Iterator_free(adt_Iterator *I);

#define adt_isetfn(i, f, n) adt_Iterator_setfn(i, f, n)
#define adt_iactual(i) adt_Iterator_actual(i)
#define adt_inext(i) adt_Iterator_next(i)
#define adt_iprev(i) adt_Iterator_previous(i)
#define adt_istarted(i) adt_Iterator_hasnext(i)
#define adt_ihasnext(i) adt_Iterator_hasnext(i)
#define adt_ihasprev(i) adt_Iterator_hasprevious(i)
#define adt_igetctnr(i) adt_Iterator_getcontainer(i)
#define adt_igetmode(i) adt_Iterator_getdirection(i)
#define adt_icmp(i, o) adt_Iterator_compare(i, o)
#define adt_igetval(i) adt_Iterator_getvalue(i)
#define adt_igetecode(i) adt_Iterator_geterror(i)
#define adt_iremove(i) adt_Iterator_remove(i)
#define adt_isetval(i, v) adt_Iterator_setvalue(i, v)
#define adt_ifree(i) adt_Iterator_free(i)

/**
 * @}
 * @ingroup adt_base_node
 * @{
 */

/* TODO */

/**
 * @}
 */

#endif
