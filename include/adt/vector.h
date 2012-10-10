#ifndef ADT_VECTOR_H_
#define ADT_VECTOR_H_

#include "adtdef.h"
#include "adt/types.h"


adt_DATA const adt_Api* adt_vectorapi;

typedef struct adt_VectorOptions_t {
    
    adt_Options options;
} adt_VectorOptions;

adt_API adt_Container* adt_Vector_new();
adt_API adt_Container* adt_Vector_newcap(size_t cap);
adt_API adt_Container* adt_Vector_newwith(adt_VectorOptions* options);

adt_API adt_VectorOptions* adt_Vector_initoptions(adt_VectorOptions *opt);

#endif
