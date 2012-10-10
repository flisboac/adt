/**
 * @file include/adt/container.h
 */

#ifndef ADT_CONTAINER_H_
#define ADT_CONTAINER_H_

#include <stddef.h>
#include "adtdef.h"
#include "adt/types.h"


/**
 * @defgroup adt_ctnr_new Creation and Disposal
 * @{
 */

adt_API int adt_dispose(adt_Container *C);
adt_API adt_Container* adt_copy(adt_Container *C);


/**
 * @}
 * @defgroup adt_ctnr_state Container State
 * @{
 */


adt_API adt_Options* adt_getoptions(adt_Container *C, adt_Options *opts);
adt_API adt_EEcode  adt_setoptions(adt_Container *C, adt_Options *opts);
adt_API adt_FHash adt_gethashf(adt_Container *C);
adt_API int adt_iscategory(adt_Container *C, adt_ECategory cat);
adt_API adt_EEcode adt_getecode(adt_Container *C);
adt_API adt_ECategory adt_getcategory(adt_Container *C);
adt_API int* adt_getcategories(adt_Container *C, int* cats);


/**
 * @}
 * @defgroup adt_ctnr_oper Control Operations
 * @{
 */


adt_API adt_EEcode adt_sort(adt_Container *C, int reverse);
adt_API adt_EEcode adt_reserve(adt_Container *C, ...);
adt_API adt_EEcode adt_resize(adt_Container *C, ...);
adt_API adt_EEcode adt_freeze(adt_Container *C);
adt_API adt_EEcode adt_swap(adt_Container *C, adt_Container *O);
adt_API adt_EEcode adt_clear(adt_Container *C);

adt_API adt_EEcode adt_rehash(adt_Container *C);


/**
 * @}
 * @defgroup adt_ctnr_access Data Access
 * @{
 */


adt_API int adt_has(adt_Container *C, ...);

adt_API adt_Value adt_get(adt_Container *C, ...);
adt_API adt_Value adt_set(adt_Container *C, ...);
adt_API adt_Value adt_remove(adt_Container *C, ...);
adt_API adt_Value adt_insert(adt_Container *C, ...);
#define adt_put adt_set

adt_API adt_EEcode adt_pushl(adt_Container *C, ...);
adt_API adt_EEcode adt_pushr(adt_Container *C, ...);
adt_API adt_Value adt_popl(adt_Container *C);
adt_API adt_Value adt_popr(adt_Container *C);
#define adt_push adt_pushr
#define adt_pop adt_popr

adt_API adt_EEcode adt_rotl(adt_Container *C, size_t count);
adt_API adt_EEcode adt_rotr(adt_Container *C, size_t count);
adt_API adt_EEcode adt_crotl(adt_Container *C, size_t count);
adt_API adt_EEcode adt_crotr(adt_Container *C, size_t count);

adt_API size_t adt_getoccurrences(adt_Container *C, ...);
adt_API adt_Value adt_removeoccurrences(adt_Container *C, size_t amount, ...);


/**
 * @}
 * @defgroup adt_ctnr_iter Iterators
 * @{
 */


adt_API adt_Iterator* adt_iterate(adt_Container *C, adt_EIteratorMode mode);
adt_API adt_Iterator* adt_iterateat(adt_Container *C, adt_EIteratorMode mode, ...);
adt_API int adt_Iterator_dispose(adt_Iterator *I);
#define adt_idispose adt_Iterator_dispose

adt_API adt_Value adt_Iterator_actual(adt_Iterator *I);
adt_API adt_Value adt_Iterator_actualkeys(adt_Iterator *I);
adt_API adt_Value adt_Iterator_next(adt_Iterator *I);
adt_API adt_Value adt_Iterator_previous(adt_Iterator *I);
#define adt_iactual adt_Iterator_actual
#define adt_ikeys adt_Iterator_actualkeys
#define adt_inext adt_Iterator_next
#define adt_iprev adt_Iterator_previous

adt_API adt_EIteratorMode adt_Iterator_getmode(adt_Iterator *I);
adt_API adt_Container* adt_Iterator_getcontainer(adt_Iterator *I);
adt_API int adt_Iterator_hasstarted(adt_Iterator *I);
adt_API int adt_Iterator_hasnext(adt_Iterator *I);
adt_API int adt_Iterator_hasprevious(adt_Iterator *I);
#define adt_igetmode adt_Iterator_getmode
#define adt_igetctnr adt_Iterator_getcontainer
#define adt_istarted adt_Iterator_hasstarted
#define adt_ihasnext adt_Iterator_hasnext
#define adt_ihasprev adt_Iterator_hasprevious

adt_API adt_EEcode adt_Iterator_set(adt_Iterator *I, adt_Value val);
adt_API adt_EEcode adt_Iterator_remove(adt_Iterator *I);
adt_API adt_EEcode adt_Iterator_compare(adt_Iterator *I, adt_Iterator *O);
#define adt_iset adt_Iterator_set
#define adt_idel adt_Iterator_remove
#define adt_icmp adt_Iterator_compare

/** @} */

#endif /* ADT_CONTAINER_H_ */
