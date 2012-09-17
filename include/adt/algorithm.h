#ifndef ADT_ALGORITHM_H_
#define ADT_ALGORITHM_H_

/**
 * @defgroup adt_algo_cmp Comparison
 * @{
 */

adt_API adt_ECmpResult adt_compare(adt_Container *C1, adt_Container *C2);

/**
 * @}
 * @defgroup adt_algo_set Sets
 * @{
 */

adt_API adt_Container* adt_union(adt_Container *C1, adt_Container *C2, adt_Container *O);
adt_API adt_Container* adt_difference(adt_Container *C1, adt_Container *C2, adt_Container *O);
adt_API adt_Container* adt_intersection(adt_Container *C1, adt_Container *C2, adt_Container *O);

/**
 * @}
 * @defgroup adt_algo_subset Subsets
 * @{
 */

adt_API adt_Container* adt_getkeys(adt_Container *C, adt_Container *O);
adt_API adt_Container* adt_getvalues(adt_Container *C, adt_Container *O);
adt_API adt_Container* adt_gethead(adt_Container *C, adt_Container *O);
adt_API adt_Container* adt_gettail(adt_Container *C, adt_Container *O);
adt_API adt_Container* adt_getrangeat(adt_Container *C, adt_Container *O, size_t from, size_t to);
adt_API adt_Container* adt_getirange(adt_Container *C, adt_Container *O, adt_Iterator *from, adt_Iterator *to);

/**
 * @}
 */

#endif
