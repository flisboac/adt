#ifndef DT_TYPES_SZ_H_
#define DT_TYPES_SZ_H_

#include "dt.h"
#include "dt/base/types.h"


typedef struct dt_SzType_ dt_SzType;

struct dt_SzType_ {
    
    dt_Type type;
    size_t defval;
};


dt_API dt_EEcode dt_SzType_valuef(void* valuep, dt_Type* T, dt_EValueAct act, size_t obj_count, void* obj, void* to);
dt_API int dt_SzType_cmpf(dt_Type* T, dt_EEcode* result, const void *a, const void* b);
dt_API size_t dt_SzType_hashf(dt_Type* T, dt_EEcode* result, const void* a);

#endif /* DT_TYPES_SZ_H_ */
