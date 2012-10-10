#ifndef ADT_ALGORITHM_H_
#define ADT_ALGORITHM_H_

#include "adtdef.h"
#include "adt/types.h"

/*
 * [ C O M P A R I S O N ]
 */


adt_API adt_ECmpResult adt_compare(adt_Container *C1, adt_Container *C2);


/*
 * [ G R O U P S ]
 */


adt_API adt_Container* adt_union(adt_Container *C1, adt_Container *C2, adt_Container *O);
adt_API adt_Container* adt_difference(adt_Container *C1, adt_Container *C2, adt_Container *O);
adt_API adt_Container* adt_intersection(adt_Container *C1, adt_Container *C2, adt_Container *O);


/*
 * [ S U B - S E T S ]
 */


adt_API adt_Container* adt_getkeys(adt_Container *C, adt_Container *O);
adt_API adt_Container* adt_getvalues(adt_Container *C, adt_Container *O);
adt_API adt_Container* adt_gethead(adt_Container *C, adt_Container *O);
adt_API adt_Container* adt_gettail(adt_Container *C, adt_Container *O);
adt_API adt_Container* adt_getrange(adt_Iterator *from, adt_Iterator *to, adt_Container *O);
adt_API adt_Value adt_first(adt_Container *C);
adt_API adt_Value adt_last(adt_Container *C);


/*
 * [ U T I L I T I E S ]
 */


adt_API adt_Container* adt_clone(adt_Container *C, adt_Container *O);


#endif
