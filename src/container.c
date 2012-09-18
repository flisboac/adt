#include <stdarg.h>
#include "objects.h"
#include "adtdefs.h"
#include "adt/types.h"
#include "adt/container.h"
#include "adt/util.h"


static adtX_ContainerApi*
getapi(
    adt_Container *C
) {
    
    adtX_ContainerApi* api = NULL;
    
    if (C)
        if (C->api)
            api = C->api;
        else
            api =getapifor(C->type);
    
    return api;
}

static adtX_ContainerApi*
getapifor(
    adt_EType type
) {
    
    adtX_ContainerApi* api = NULL;
    
    if (adt_EType_isvalid(type))
        api = adtX_apis[type];
    
    return api;
}

/*
 * [ N E W ] ===================================================================
 * Container creation
 */

adt_Container *
adt_new(
	adt_EType ctype, ...
) {
	
    va_list args;
	adt_Container *C = NULL;
    adtX_ContainerApi *api = getapifor(ctype);
    
    if (api && api->new_) {
        va_start(args, ctype);
        C = api->new_(ctype, args);
        va_end(args);
    }
    
    return C;
}

adt_Container *
adt_newwith(
	adt_Options *options
) {
	
    va_list args;
	adt_Container *C = NULL;
    adtX_ContainerApi *api;
    
    if (!options) return NULL;
    api = getapifor(options->type);
    
    if (api && api->newwith) {
        va_start(args, ctype);
        C = api->newwith(options);
        va_end(args);
    }
    
    return C;
}

void 
adt_free(
	adt_Container *C
) {
	
    adtX_ContainerApi *api = getapi(C);
    
	if (C && api) {
        
        if (api->free)
            api->free(C);
	}
}

adt_Container *
adt_copy(
	adt_Container *C
) {
    
	adt_Container *O = NULL;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->copy)
            O = api->copy(C);
        else
            C->ecode = adt_EC_NSUPP;
	}
    
    return O;
}


/*
 * [ A C C E S S ] =============================================================
 * Container data access
 */

/* Has */
size_t 
adt_has(
	adt_Container *C, ...
) {
	
    va_list args;
	size_t status = 0;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->has) {
            va_start(args, C);
            status = api->has(C, args);
            va_end(args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return status;
}

size_t 
adt_hasvalue(
	adt_Container *C, ...
) {
    
    va_list args;
	size_t status = 0;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->hasvalue) {
            va_start(args, C);
            status = api->hasvalue(C, args);
            va_end(args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return status;
}


/* Get */
adt_Value 
adt_get(
	adt_Container *C, ...
) {
	
	adt_Value V = adtNONE;
    va_list args;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->get) {
            va_start(args, C);
            V = api->get(C, args);
            va_end(args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return V;
}

size_t 
adt_occurrences(
	adt_Container *C, ...
) {
	
    size_t V = 0;
    va_list args;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->occurrences) {
            va_start(args, C);
            V = api->occurrences(C, args);
            va_end(args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return V;
}

adt_Value 
adt_getfirst(
	adt_Container *C
) {
	
	adt_Value V = adtNONE;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->getfirst) {
            V = api->getfirst(C);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return V;
}

adt_Value 
adt_getlast(
	adt_Container *C
) {
	
	adt_Value V = adtNONE;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->getlast) {
            V = api->getlast(C);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return V;
}


/* Set */
adt_Value 
adt_set(
	adt_Container *C, ...
) {
	
	adt_Value V = adtNONE;
    va_list args;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->set) {
            va_start(args, C);
            V = api->set(C, args);
            va_end(args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return V;
}


/* Push */
adt_EEcode 
adt_push(
	adt_Container *C, ...
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    va_list args;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->push) {
            va_start(args, C);
            ecode = api->push(C, args);
            va_end(args);
            
        } else
            C->ecode = ecode = adt_EC_NSUPP;
    }
    
    return ecode;
}

adt_EEcode 
adt_pushl(
	adt_Container *C, ...
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    va_list args;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->pushl) {
            va_start(args, C);
            ecode = api->pushl(C, args);
            va_end(args);
            
        } else
            C->ecode = ecode = adt_EC_NSUPP;
    }
    
    return ecode;
}

adt_EEcode 
adt_pushr(
	adt_Container *C, ...
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    va_list args;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->pushr) {
            va_start(args, C);
            ecode = api->pushr(C, args);
            va_end(args);
            
        } else
            C->ecode = ecode = adt_EC_NSUPP;
    }
    
    return ecode;
}

adt_Value 
adt_pop(
	adt_Container *C
) {
	
	adt_Value V = adtNONE;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->pop) {
            V = api->pop(C, args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return V;
}

adt_Value 
adt_popl(
	adt_Container *C
) {
	
	adt_Value V = adtNONE;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->popl) {
            V = api->popl(C, args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return V;
}

adt_Value 
adt_popr(
	adt_Container *C
) {
	
	adt_Value V = adtNONE;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->popr) {
            V = api->popr(C, args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return V;
}


/* Insertion */
adt_EEcode 
adt_insert(
	adt_Container *C, ...
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    va_list args;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->insert) {
            va_start(args, C);
            ecode = api->insert(C, args);
            va_end(args);
            
        } else
            C->ecode = ecode = adt_EC_NSUPP;
    }
    
    return ecode;
}

adt_Value 
adt_remove(
	adt_Container *C, ...
) {
	
	adt_Value V = adtNONE;
    va_list args;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->remove) {
            va_start(args, C);
            V = api->remove(C, args);
            va_end(args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return V;
}

adt_Value 
adt_removeoccurrences(
	adt_Container *C, ...
) {
	
	adt_Value V = adtNONE;
    va_list args;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->removeall) {
            va_start(args, C);
            V = api->removeoccurrences(C, args);
            va_end(args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return V;
}


/* Indexof */
adt_Value 
adt_index(
	adt_Container *C, ...
) {
	
	adt_Value V = adtNONE;
    va_list args;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->index) {
            va_start(args, C);
            V = api->index(C, args);
            va_end(args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return V;
}

adt_Value 
adt_rindex(
	adt_Container *C, ...
) {
	
	adt_Value V = adtNONE;
    va_list args;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->rindex) {
            va_start(args, C);
            V = api->rindex(C, args);
            va_end(args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return V;
}


/* Shifts */
adt_EEcode 
adt_rotl(
	adt_Container *C, size_t count
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->rotl) {
            ecode = api->rotl(C, count);
            
        } else
            C->ecode = ecode = adt_EC_NSUPP;
    }
    
    return ecode;
}

adt_EEcode 
adt_rotr(
	adt_Container *C, size_t count
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    va_list args;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->rotr) {
            ecode = api->rotr(C, count);
            
        } else
            C->ecode = ecode = adt_EC_NSUPP;
    }
    
    return ecode;
}

adt_EEcode 
adt_crotl(
	adt_Container *C, size_t count
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->crotl) {
            ecode = api->crotl(C, count);
            
        } else
            C->ecode = ecode = adt_EC_NSUPP;
    }
    
    return ecode;
}

adt_EEcode 
adt_crotr(
	adt_Container *C, size_t count
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->crotr) {
            ecode = api->crotr(C, count);
            
        } else
            C->ecode = ecode = adt_EC_NSUPP;
    }
    
    return ecode;
}


/*
 * [ A C T I O N ] =============================================================
 * Container actions and operations
 */

adt_EEcode 
adt_sort(
	adt_Container *C
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->sort) {
            ecode = api->sort(C);
            
        } else
            C->ecode = ecode = adt_EC_NSUPP;
    }
    
    return ecode;
}

adt_EEcode 
adt_resize(
	adt_Container *C, ...
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    va_list args;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->resize) {
            va_start(args);
            ecode = api->resize(C, args);
            va_end(args);
            
        } else
            C->ecode = ecode = adt_EC_NSUPP;
    }
    
    return ecode;
}

adt_EEcode 
adt_reserve(
	adt_Container *C, ...
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    va_list args;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->reserve) {
            va_start(args);
            ecode = api->reserve(C, args);
            va_end(args);
            
        } else
            C->ecode = ecode = adt_EC_NSUPP;
    }
    
    return ecode;
}

adt_EEcode 
adt_swap(
	adt_Container *C, adt_Container *O
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->reserve) {
            ecode = api->reserve(C, O);
            
        } else
            C->ecode = ecode = adt_EC_NSUPP;
    }
    
    return ecode;
}

adt_EEcode 
adt_rehash(
	adt_Container *C
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->rehash) {
            ecode = api->rehash(C);
            
        } else
            C->ecode = ecode = adt_EC_NSUPP;
    }
    
    return ecode;
}

adt_EEcode 
adt_clear(
	adt_Container *C
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->clear) {
            ecode = api->clear(C);
            
        } else
            C->ecode = ecode = adt_EC_NSUPP;
    }
    
    return ecode;
}


/*
 * [ S T A T E ] ===============================================================
 * Container state
 */

void 
adt_getoptions(
	adt_Container *C, adt_Options *to
) {
	
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->getoptions) {
            ecode = api->getoptions(C, to);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
}

adt_EEcode 
adt_getecode(
	adt_Container *C
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    
    if (C)
        ecode = C->ecode;
    
    return ecode;
}

size_t 
adt_getlen(
	adt_Container *C
) {
	
	size_t len = 0;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->getlen) {
            len = api->getlen(C);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return len;
}

size_t 
adt_getcap(
	adt_Container *C
) {
	
	size_t cap = 0;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->getcap) {
            len = api->getcap(C);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return cap;
}

size_t 
adt_getcount(
	adt_Container *C
) {
	
	size_t count = 0;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->getcount) {
            len = api->getcount(C);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return count;
}

adt_Value 
adt_getkeytype(
	adt_Container *C
) {
	
	adt_Value V = adtNONE;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->getkeytype) {
            V = api->getkeytype(C, args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return V;
}

adt_Value 
adt_getvaluetype(
	adt_Container *C
) {
	
	adt_Value V = adtNONE;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->getvaluetype) {
            V = api->getvaluetype(C, args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return V;
}

adt_Value 
adt_getdefault(
	adt_Container *C
) {
	
	adt_Value V = adtNONE;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->getdefault) {
            V = api->getdefault(C, args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return V;
}

adt_ECategory*
adt_getcategories(
	adt_Container *C, adt_ECategory *list
) {
	
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->getcategories) {
            list = api->getcategories(C, list);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return list;
}


int 
adt_canreserve(
	adt_Container *C
) {
	
	int status = 0;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->canreserve) {
            status = api->canreserve(C, args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return status;
}

int 
adt_canresize(
	adt_Container *C
) {
	
	int status = 0;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->canresize) {
            status = api->canresize(C, args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return status;
}

int 
adt_canchange(
	adt_Container *C
) {
	
	int status = 0;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->canchange) {
            status = api->canchange(C, args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return status;
}

int 
adt_isempty(
	adt_Container *C
) {
	
	int status = -1;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->isempty) {
            status = api->isempty(C, args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return status;
}

int 
adt_isautofree(
	adt_Container *C
) {
	
	int status = 0;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->isautofree) {
            status = api->isautofree(C, args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return status;
}

int 
adt_isautoorder(
	adt_Container *C
) {
	
	int status = 0;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->isautoorder) {
            status = api->isautoorder(C, args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return status;
}


adt_Value 
adt_setdefault(
	adt_Container *C
) {
	
	adt_Value V = adtNONE;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->rindex) {
            V = api->rindex(C, args);
            
        } else
            C->ecode = adt_EC_NSUPP;
    }
    
    return V;
}

adt_EEcode 
adt_setimmutable(
	adt_Container *C
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->clear) {
            ecode = api->clear(C);
            
        } else
            C->ecode = ecode = adt_EC_NSUPP;
    }
    
    return ecode;
}

adt_EEcode 
adt_setresizemult(
	adt_Container *C, size_t mult
) {
	
    adt_EEcode ecode = adt_EC_ERROR;
    adtX_ContainerApi *api = getapi(C);
    
    if (C && api) {
        C->ecode = adt_EC_OK;
        
        if (api->clear) {
            ecode = api->clear(C, mult);
            
        } else
            C->ecode = ecode = adt_EC_NSUPP;
    }
    
    return ecode;
}

adt_EEcode 
adt_setautofree(
	adt_Container *C, int flag
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    return ecode;
}

adt_EEcode 
adt_setautoorder(
	adt_Container *C, int flag
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    return ecode;
}

adt_EEcode 
adt_sethashf(
	adt_Container *C, adt_FHash hashf
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    return ecode;
}

adt_EEcode 
adt_setfinalizerf(
	adt_Container *C, adt_FFinalize finalizef
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    return ecode;
}

adt_EEcode 
adt_setcomparef(
	adt_Container *C, adt_FCompare hashf
) {
	
	adt_EEcode ecode = adt_EC_ERROR;
    return ecode;
}


/*
 * [ I T E R A T O R S ] =======================================================
 * Iterators
 */

adt_Iterator* 
adt_iterator(
	adt_Container *C, adt_EIteratorMode mode, int autofree
) {
	
	adt_Iterator *I = NULL;
    return I;
}

adt_Iterator* 
adt_iteratorat(
	adt_Container *C, adt_EIteratorMode mode, int autofree, ...
) {
	
	adt_Iterator *I = NULL;
    return I;
}


adt_EEcode 
adt_Iterator_setfn(
	adt_Iterator *I, adt_FIterate fn, void* state
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_Value 
adt_Iterator_actual(
	adt_Iterator *I
) {
	
	adt_Value V = adtNONE;
    return V;
}

adt_Value 
adt_Iterator_next(
	adt_Iterator *I
) {
	
	adt_Value V = adtNONE;
    return V;
}

adt_Value 
adt_Iterator_previous(
	adt_Iterator *I
) {
	
	adt_Value V = adtNONE;
    return V;
}

int 
adt_Iterator_hasstarted(
	adt_Iterator *I
) {
	
	int status = 0;
    return status;
}

int 
adt_Iterator_hasnext(
	adt_Iterator *I
) {
	
	int status = 0;
    return status;
}

int 
adt_Iterator_hasprevious(
	adt_Iterator *I
) {
	
	int status = 0;
    return status;
}

adt_EIteratorMode 
adt_Iterator_getmode(
	adt_Iterator *I
) {
	
	adt_EIteratorMode mode = adt_ITER_NONE;
    return mode;
}

adt_ECmpResult 
adt_Iterator_compare(
	adt_Iterator *I, adt_Iterator *O
) {
	
	adt_ECmpResult result = adt_CMP_ERR;
    return result;
}

adt_Container* 
adt_Iterator_getcontainer(
	adt_Iterator *I
) {
	
	adt_Container *C = NULL;
    return C;
}

adt_Value 
adt_Iterator_getvalue(
	adt_Iterator *I
) {
	
	adt_Value V = adtNONE;
    return V;
}

adt_EEcode 
adt_Iterator_getecode(
	adt_Iterator *I
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_EEcode 
adt_Iterator_remove(
	adt_Iterator *I
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_EEcode 
adt_Iterator_setvalue(
	adt_Iterator *I, adt_Value val
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

void 
adt_Iterator_free(
	adt_Iterator *I
) {
	
	
}
