#ifndef DT_TYPES_CSTR_H_
#define DT_TYPES_CSTR_H_

#include "dt.h"
#include "dt/base/types.h"


typedef struct dt_CstrType_ dt_CstrType;

struct dt_CstrType_ {
    
    dt_Type type;
    dt_EStrCmpMethod cmp_method;
    char* defval;
};


dt_API dt_EEcode dt_CstrType_valuef(void* valuep, dt_Type* T, dt_EValueAct act, size_t obj_count, void* obj, void* to);
dt_API int dt_CstrType_cmpf(dt_Type* T, dt_EEcode* result, const void *a, const void* b);
dt_API size_t dt_CstrType_hashf(dt_Type* T, dt_EEcode* result, const void* a);


#endif /* DT_TYPES_CSTR_H_ */
