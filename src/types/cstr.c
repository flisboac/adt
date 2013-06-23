#include "dt/types/cstr.h"



static dt_CstrType dt_cstr_typeData = {
    {
        /* base    */ NULL
        /* rawtype */ , dt_RAW_CSTR
        /* name    */ , "cstr"
        /* size    */ , sizeof(dt_cstr)
        /* cmpf    */ , dt_CstrType_cmpf
        /* hashf   */ , dt_CstrType_hashf
        /* valuef  */ , dt_CstrType_valuef
        /* valuep  */ , NULL
    }
    , dt_CSTR_CMP_COLL
    , NULL
};


dt_EEcode 
dt_CstrType_valuef(
    void* valuep
    , dt_Type* T
    , dt_EValueAct act
    , size_t obj_count
    , void* obj
    , void* to
) {
    dt_EEcode ecode = dt_ERROR;
    dt_CstrType* Tcstr = (dt_CstrType*)T;
    dt_cstr* ptr = (dt_cstr*)obj;
    dt_cstr* ptr2 = (dt_cstr*) to;
    size_t i;
    
    if (Tcstr && obj && obj_count > 0) {
        switch(act) {
            case dt_VAL_INIT:
                for (i = 0; i < obj_count; i++) *ptr++ = NULL;
                ecode = dt_OK;
                break;
                
            case dt_VAL_QUIT:
                ecode = dt_OK;
                break;
                
            case dt_VAL_COPY:
                for (i = 0; i < obj_count; i++)
                    *ptr2++ = *ptr++;
                ecode = dt_OK;
                break;
        }
    }
    return ecode;
}

int
dt_CstrType_cmpf(
    dt_Type* T
    , dt_EEcode* result
    , const void *a
    , const void* b
) {
    int cmp = 0;
    dt_CstrType* Tcstr = (dt_CstrType*)T;
    
    if (result)
        *result = dt_ERROR;
        
    if (Tcstr && a && b) {
        switch (Tcstr->cmp_method) {
            case dt_CSTR_CMP_CMP:
                cmp = strcmp((dt_cstr)a, (dt_cstr)b);
                if (result) *result = dt_OK;
                break;
                
            case dt_CSTR_CMP_COLL:
                cmp = strcoll((dt_cstr)a, (dt_cstr)b);
                if (result) *result = dt_OK;
                break;
        }
    }
    
    return cmp;
}

size_t
dt_CstrType_hashf(
    dt_Type* T
    , dt_EEcode* result
    , const void* a
) {
    unsigned long hash = dt_NOSIZE;
    char c, *str = (dt_cstr)a;
    
    if (result) result = dt_ERROR;
    
    if (T && a) {
        hash = 5381;
        while (c = *str++) hash = ((hash << 5) + hash) + c;
        if (result) result = dt_OK;
    }
    
    return hash;
}
