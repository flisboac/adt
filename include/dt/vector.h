#ifndef DT_VECTOR_H_
#define DT_VECTOR_H_


#include <stddef.h>
#include "dtcfg.h"
#include "dt/base/types.h"


typedef struct dt_Vector_     dt_Vector;
typedef struct dt_VectorIter_ dt_VectorIter;


struct dt_VectorIter_ {

    dt_Iter      iter;
    dt_Vector*   ctnr;
    size_t       pos;
    dt_EIterMode mode;
    int          started;
};


struct dt_Vector_ {

    dt_Vector    ctnr;
    dt_Type*   vtype; /* DOES NOT OWN */
    dt_State*  state; /* OWNS */
    dt_Buffer* data;  /* MAY NOT OWN */
};


/* Allocation */
dt_API dt_Vector* dt_Vector_create(const dt_VectorApi* type);
dt_API dt_Vector* dt_Vector_createfor(const dt_VectorApi* type, const dt_Type* vtype, const dt_Type* ktype);
dt_API dt_Vector* dt_Vector_createwith(const dt_VectorApi* type, dt_Opts* opts);
dt_API dt_EEcode dt_Vector_initwith(dt_Vector* C, dt_Opts* opts);
dt_API dt_EEcode dt_Vector_finalize(dt_Vector* C);
dt_API dt_EEcode dt_Vector_dispose(dt_Vector* C);
dt_API dt_EEcode dt_Vector_swap(dt_Vector *C, dt_Vector *O);
dt_API dt_Vector* dt_Vector_dup(dt_Vector* C);

/* State */
dt_API dt_EEcode dt_Vector_getecode(dt_Vector* C);
dt_API dt_State* dt_Vector_getstate(dt_Vector* C, dt_State* S);
dt_API dt_EEcode dt_Vector_setstate(dt_Vector* C, dt_State* S);
dt_API dt_EEcode dt_Vector_getprop(dt_Vector* C, int prop, void* val);
dt_API dt_EEcode dt_Vector_setprop(dt_Vector* C, int prop, void* val);
dt_API size_t dt_Vector_getlen(dt_Vector* C);
dt_API size_t dt_Vector_getcap(dt_Vector* C);

/* Data */
dt_API size_t dt_Vector_has(dt_Vector* C, ... /* k */);
dt_API void* dt_Vector_get(dt_Vector* C, ... /* k */);
dt_API dt_EEcode dt_Vector_put(dt_Vector* C, ... /* p, k */);
dt_API dt_EEcode dt_Vector_set(dt_Vector* C, ... /* p, v, k */);
dt_API dt_EEcode dt_Vector_insert(dt_Vector* C, ... /* v, k */);
dt_API dt_EEcode dt_Vector_remove(dt_Vector* C, ... /* p, k */);
dt_API dt_EEcode dt_Vector_flip(dt_Vector* C, ... /* p, k */);
dt_API dt_EEcode dt_Vector_reset(dt_Vector*C, ... /* p, k */);
dt_API size_t dt_Vector_removec(dt_Vector* C, size_t amount, ... /* k */);

/* Bit data */
/* NO BIT DATA ACCESS */

/* Operations */
dt_API dt_EEcode dt_Vector_sort(dt_Vector *C, int reverse);
dt_API dt_EEcode dt_Vector_reverse(dt_Vector* C);
dt_API dt_EEcode dt_Vector_reserve(dt_Vector *C, size_t size);
dt_API dt_EEcode dt_Vector_resize(dt_Vector *C, size_t size);
dt_API dt_EEcode dt_Vector_rehash(dt_Vector* C);
dt_API dt_EEcode dt_Vector_zip(dt_Vector* C);
dt_API dt_EEcode dt_Vector_clear(dt_Vector *C);

#if 0
/* The following will be left to be supplied by the frontend api. */

/* Shift */
dt_API dt_EEcode dt_Vector_push(dt_Vector* C, ... /* v */);
dt_API dt_EEcode dt_Vector_pushi(dt_Vector* C, ... /* v */);
dt_API void* dt_Vector_pop(dt_Vector* C, ... /* *v */);
dt_API void* dt_Vector_popi(dt_Vector* C, ... /* *v */);
#define dt_Vector_pushl dt_Vector_pushi
#define dt_Vector_pushr dt_Vector_push
#define dt_Vector_popl dt_Vector_popi
#define dt_Vector_popr dt_Vector_pop
dt_API size_t dt_Vector_rot(dt_Vector* C, size_t count);
dt_API size_t dt_Vector_roti(dt_Vector* C, size_t count);
dt_API size_t dt_Vector_crot(dt_Vector* C, size_t count);
dt_API size_t dt_Vector_croti(dt_Vector* C, size_t count);
#define dt_Vector_rotl dt_Vector_roti
#define dt_Vector_rotr dt_Vector_rot
#define dt_Vector_crotl dt_Vector_croti
#define dt_Vector_crotr dt_Vector_crot

#endif

#endif
