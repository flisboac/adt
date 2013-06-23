#ifndef DT_TYPES_CTNR_H_
#define DT_TYPES_CTNR_H_

#include "dt.h"
#include "dt/base/types.h"

typedef struct dt_CtnrType_ dt_CtnrType;

struct dt_CtnrType_ {
    
    dt_Type  type;
};


dt_API dt_EEcode dt_CtnrType_valuef(void* valuep, dt_Type* T, dt_EValueAct act, size_t obj_count, void* obj, void* to);
dt_API int dt_CtnrType_cmpf(dt_Type* T, dt_EEcode* result, const void *a, const void* b);
dt_API size_t dt_CtnrType_hashf(dt_Type* T, dt_EEcode* result, const void* a);


#endif /* DT_TYPES_CTNR_H_ */
