#include "objects.h"

const adt_ECategory[] adtX_categories[] = {
    
    /* adt_TYPE_NONE   */  {adt_CAT_NONE}
    /* adt_TYPE_VECTOR */, {adt_CAT_SEQ, adt_CAT_LIST, adt_CAT_NONE}
};


const int adtX_implemented[] = {
    
    /* adt_TYPE_NONE   */  0
    /* adt_TYPE_VECTOR */, 0
};


const adtX_ContainerApi const* adtX_apis[] = {
    
    /* adt_TYPE_NONE   */  NULL
    /* adt_TYPE_VECTOR */, &adtX_api_vector
};
