#ifndef DT_TYPES_ARRAY_H_
#define DT_TYPES_ARRAY_H_

#include "dt.h"
#include "dt/base/types.h"

typedef struct dt_ArrayType_ dt_ArrayType;

struct dt_ArrayType_ {
    
    dt_Type  type;
    size_t   size;
    
    /* `type.base` holds the base type for the array. */
};


dt_API dt_EEcode dt_ArrayType_valuef(void* valuep, dt_Type* T, dt_EValueAct act, size_t obj_count, void* obj, void* to);
dt_API int dt_ArrayType_cmpf(dt_Type* T, dt_EEcode* result, const void *a, const void* b);
dt_API size_t dt_ArrayType_hashf(dt_Type* T, dt_EEcode* result, const void* a);


#endif /* DT_TYPES_ARRAY_H_ */
