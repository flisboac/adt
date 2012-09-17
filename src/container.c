#include <stdarg.h>
#include "objects.h"
#include "adt/container.h"

/*
 * [ N E W ] ===================================================================
 * Container creation
 */

adt_Container *
adt_new
	adt_EType ctype, ...
) {
	
	adt_Container *C = NULL;
    return C;
}

adt_Container *
adt_newwith
	adt_Options *options
) {
	
	adt_Container *C = NULL;
    return C;
}

void 
adt_free
	adt_Container *C
) {
	
	
}

adt_Container *
adt_copy
	adt_Container *C
) {
	
    adt_Container *C = NULL;
    return C;
}


/*
 * [ A C C E S S ] =============================================================
 * Container data access
 */

/* Has */
size_t 
adt_has
	adt_Container *C, ...
) {
	
	size_t status = 0;
    return status;
}

size_t 
adt_hasvalue
	adt_Container *C, ...
) {
	
    size_t status = 0;
    return status;
}


/* Get */
adt_Value 
adt_get
	adt_Container *C, ...
) {
	
	adt_Value V = adtNONE;
    return V;
}

adt_Value 
adt_ocurrences
	adt_Container *C, ...
) {
	
    adt_Value V = adtNONE;
    return V;
}

adt_Value 
adt_getfirst
	adt_Container *C
) {
	
	adt_Value V = adtNONE;
    return V;
}

adt_Value 
adt_getlast
	adt_Container *C
) {
	
	adt_Value V = adtNONE;
    return V;
}


/* Set */
adt_Value 
adt_set
	adt_Container *C, ...
) {
	
	adt_Value V = adtNONE;
    return V;
}


/* Push */
adt_EEcode 
adt_push
	adt_Container *C, ...
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_EEcode 
adt_pushl
	adt_Container *C, ...
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_EEcode 
adt_pushr
	adt_Container *C, ...
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_Value 
adt_pop
	adt_Container *C
) {
	
	adt_Value V = adtNONE;
    return V;
}

adt_Value 
adt_popl
	adt_Container *C
) {
	
	adt_Value V = adtNONE;
    return V;
}

adt_Value 
adt_popr
	adt_Container *C
) {
	
	adt_Value V = adtNONE;
    return V;
}


/* Insertion */
adt_EEcode 
adt_insert
	adt_Container *C, ...
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_Value 
adt_remove
	adt_Container *C, ...
) {
	
	adt_Value V = adtNONE;
    return V;
}

adt_Value 
adt_removeall
	adt_Container *C, ...
) {
	
	adt_Value V = adtNONE;
    return V;
}


/* Indexof */
adt_Value 
adt_index
	adt_Container *C, ...
) {
	
	adt_Value V = adtNONE;
    return V;
}

adt_Value 
adt_rindex
	adt_Container *C, ...
) {
	
	adt_Value V = adtNONE;
    return V;
}


/* Shifts */
adt_EEcode 
adt_rotl
	adt_Container *C, size_t count
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_EEcode 
adt_rotr
	adt_Container *C, size_t count
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_EEcode 
adt_crotl
	adt_Container *C, size_t count
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_EEcode 
adt_crotr
	adt_Container *C, size_t count
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}


/*
 * [ A C T I O N ] =============================================================
 * Container actions and operations
 */

adt_EEcode 
adt_sort
	adt_Container *C
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_EEcode 
adt_resize
	adt_Container *C, ...
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_EEcode 
adt_reserve
	adt_Container *C, ...
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_EEcode 
adt_swap
	adt_Container *C, adt_Container *O
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_EEcode 
adt_rehash
	adt_Container *C
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_EEcode 
adt_clear
	adt_Container *C
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}


/*
 * [ S T A T E ] ===============================================================
 * Container state
 */

void 
adt_getoptions
	adt_Container *C, adt_Options *to
) {
	
	
}

adt_EEcode 
adt_getecode
	adt_Container *C
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

size_t 
adt_getlen
	adt_Container *C
) {
	
	size_t len = 0;
    return len;
}

size_t 
adt_getcap
	adt_Container *C
) {
	
	size_t cap = 0;
    return cap;
}

size_t 
adt_getcount
	adt_Container *C
) {
	
	size_t count = 0;
    return count;
}

adt_Value 
adt_getkeytype
	adt_Container *C
) {
	
	adt_Value V = adtNONE;
    return V;
}

adt_Value 
adt_getvaluetype
	adt_Container *C
) {
	
	adt_Value V = adtNONE;
    return V;
}

adt_Value 
adt_getdefault
	adt_Container *C
) {
	
	adt_Value V = adtNONE;
    return V;
}

adt_ECategory[] 
adt_getcategories
	adt_Container *C
) {
	
	adt_ECategory list[] = {adt_CAT_NONE};
    return list;
}


int 
adt_canreserve
	adt_Container *C
) {
	
	int status = 0;
    return status;
}

int 
adt_canresize
	adt_Container *C
) {
	
	int status = 0;
    return status;
}

int 
adt_canchange
	adt_Container *C
) {
	
	int status = 0;
    return status;
}

int 
adt_isempty
	adt_Container *C
) {
	
	int status = 0;
    return status;
}

int 
adt_isautofree
	adt_Container *C
) {
	
	int status = 0;
    return status;
}

int 
adt_isautoorder
	adt_Container *C
) {
	
	int status = 0;
    return status;
}


adt_Value 
adt_setdefault
	adt_Container *C
) {
	
	adt_Value V = adtNONE;
    return V;
}

adt_EEcode 
adt_setimmutable
	adt_Container *C
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

int 
adt_setresizemult
	adt_Container *C, size_t mult
) {
	
	int status = 0;
    return status;
}

adt_EEcode 
adt_setautofree
	adt_Container *C, int flag
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_EEcode 
adt_setautoorder
	adt_Container *C, int flag
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_EEcode 
adt_sethashf
	adt_Container *C, adt_FHash hashf
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_EEcode 
adt_setfinalizerf
	adt_Container *C, adt_FFinalize finalizef
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_EEcode 
adt_setcomparef
	adt_Container *C, adt_FCompare hashf
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}


/*
 * [ I T E R A T O R S ] =======================================================
 * Iterators
 */

adt_Iterator* 
adt_iterator
	adt_Container *C, adt_EIteratorMode mode, int autofree
) {
	
	adt_Iterator *I = NULL;
    return I;
}

adt_Iterator* 
adt_iteratorat
	adt_Container *C, adt_EIteratorMode mode, int autofree, ...
) {
	
	adt_Iterator *I = NULL;
    return I;
}


adt_EEcode 
adt_Iterator_setfn
	adt_Iterator *I, adt_FIterate fn, void* state
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_Value 
adt_Iterator_actual
	adt_Iterator *I
) {
	
	adt_Value V = adtNONE;
    return V;
}

adt_Value 
adt_Iterator_next
	adt_Iterator *I
) {
	
	adt_Value V = adtNONE;
    return V;
}

adt_Value 
adt_Iterator_previous
	adt_Iterator *I
) {
	
	adt_Value V = adtNONE;
    return V;
}

int 
adt_Iterator_hasstarted
	adt_Iterator *I
) {
	
	int status = 0;
    return status;
}

int 
adt_Iterator_hasnext
	adt_Iterator *I
) {
	
	int status = 0;
    return status;
}

int 
adt_Iterator_hasprevious
	adt_Iterator *I
) {
	
	int status = 0;
    return status;
}

adt_EIteratorMode 
adt_Iterator_getmode
	adt_Iterator *I
) {
	
	adt_EIteratorMode mode = adt_ITER_NONE;
    return mode;
}

adt_ECmpResult 
adt_Iterator_compare
	adt_Iterator *I, adt_Iterator *O
) {
	
	adt_ECmpResult result = adt_CMP_ERR;
    return result;
}

adt_Container* 
adt_Iterator_getcontainer
	adt_Iterator *I
) {
	
	adt_Container *C = NULL;
    return C;
}

adt_Value 
adt_Iterator_getvalue
	adt_Iterator *I
) {
	
	adt_Value V = adtNONE;
    return V;
}

adt_EEcode 
adt_Iterator_getecode
	adt_Iterator *I
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_EEcode 
adt_Iterator_remove
	adt_Iterator *I
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

adt_EEcode 
adt_Iterator_setvalue
	adt_Iterator *I, adt_Value val
) {
	
	adt_EEcode ecode = adt_EC_NIMPL;
    return ecode;
}

void 
adt_Iterator_free
	adt_Iterator *I
) {
	
	
}
