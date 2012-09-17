#include <stddef.h>
#include <stdarg.h>
#include "vector.h"

const adtX_ContainerApi adtX_api_vector = {
    
    /*
     * [ N E W ]
     */
    
    adtX_Vector_new
	, adtX_Vector_newwith
	, adtX_Vector_free
	, adtX_Vector_copy
    
    /*
     * [ A C E S S ]
     */
    
	, adtX_Vector_has
	, adtX_Vector_hasvalue
    
	, adtX_Vector_get
	, adtX_Vector_ocurrences
	, adtX_Vector_getfirst
	, adtX_Vector_getlast
    
	, adtX_Vector_set
    
	, adtX_Vector_pushr
	, adtX_Vector_pushl
	, adtX_Vector_pushr
	, adtX_Vector_popr
	, adtX_Vector_popl
	, adtX_Vector_popr
    
	, adtX_Vector_insert
	, adtX_Vector_remove
	, adtX_Vector_removeall
    
	, adtX_Vector_index
	, adtX_Vector_rindex
    
	, adtX_Vector_rotl
	, adtX_Vector_rotr
	, adtX_Vector_crotl
	, adtX_Vector_crotr
    
    /*
     * [ A C T I O N ]
     */
    
	, adtX_Vector_sort
	, adtX_Vector_resize
	, adtX_Vector_reserve
	, adtX_Vector_swap
	, adtX_Vector_rehash
	, adtX_Vector_clear
    
    /*
     * [ S T A T E ]
     */
    
	, adtX_Vector_getoptions
	, adtX_Vector_getecode
	, adtX_Vector_getlen
	, adtX_Vector_getcap
	, adtX_Vector_getcount
	, adtX_Vector_getkeytype
	, adtX_Vector_getvaluetype
	, adtX_Vector_getdefault
	, adtX_Vector_getcategories
    
	, adtX_Vector_canreserve
	, adtX_Vector_canresize
	, adtX_Vector_canchange
	, adtX_Vector_isempty
	, adtX_Vector_isautofree
	, adtX_Vector_isautoorder
    
	, adtX_Vector_setdefault
	, adtX_Vector_setimmutable
	, adtX_Vector_setresizemult
	, adtX_Vector_setautofree
	, adtX_Vector_setautoorder
	, adtX_Vector_sethashf
	, adtX_Vector_setfinalizerf
	, adtX_Vector_setcomparef
    
    /*
     * [ I T E R ]
     */
    
	, adtX_Vector_iterator
	, adtX_Vector_iteratorat
};


/*
 * [ N E W ] ===================================================================
 */

adt_Container *
adtX_Vector_new(
	adt_EType ctype, va_list args
) {
	
	adt_Container *C = NULL;
}

adt_Container *
adtX_Vector_newwith(
	adt_Options *options
) {
	
	
}

void 
adtX_Vector_free(
	adt_Container *C
) {
	
	
}

adt_Container *
adtX_Vector_copy(
	adt_Container *C
) {
	
	
}


/*
 * [ A C E S S ] ===============================================================
 */

size_t 
adtX_Vector_has(
	adt_Container *C, va_list args
) {
	
	
}

size_t 
adtX_Vector_hasvalue(
	adt_Container *C, va_list args
) {
	
	
}


adt_Value 
adtX_Vector_get(
	adt_Container *C, va_list args
) {
	
	
}

adt_Value 
adtX_Vector_ocurrences(
	adt_Container *C, va_list args
) {
	
	
}

adt_Value 
adtX_Vector_getfirst(
	adt_Container *C
) {
	
	
}

adt_Value 
adtX_Vector_getlast(
	adt_Container *C
) {
	
	
}


adt_Value 
adtX_Vector_set(
	adt_Container *C, va_list args
) {
	
	
}


/* push is pushl */
adt_EEcode 
adtX_Vector_pushl(
	adt_Container *C, va_list args
) {
	
	
}

adt_EEcode 
adtX_Vector_pushr(
	adt_Container *C, va_list args
) {
	
	
}

/* pop is popl */
adt_Value 
adtX_Vector_popl(
	adt_Container *C
) {
	
	
}

adt_Value 
adtX_Vector_popr(
	adt_Container *C
) {
	
	
}


adt_EEcode 
adtX_Vector_insert(
	adt_Container *C, va_list args
) {
	
	
}

adt_Value 
adtX_Vector_remove(
	adt_Container *C, va_list args
) {
	
	
}

adt_Value 
adtX_Vector_removeall(
	adt_Container *C, va_list args
) {
	
	
}


adt_Value 
adtX_Vector_index(
	adt_Container *C, va_list args
) {
	
	
}

adt_Value 
adtX_Vector_rindex(
	adt_Container *C, va_list args
) {
	
	
}


adt_EEcode 
adtX_Vector_rotl(
	adt_Container *C, size_t count
) {
	
	
}

adt_EEcode 
adtX_Vector_rotr(
	adt_Container *C, size_t count
) {
	
	
}

adt_EEcode 
adtX_Vector_crotl(
	adt_Container *C, size_t count
) {
	
	
}

adt_EEcode 
adtX_Vector_crotr(
	adt_Container *C, size_t count
) {
	
	
}


/*
 * [ A C T I O N ] =============================================================
 */

adt_EEcode 
adtX_Vector_sort(
	adt_Container *C
) {
	
	
}

adt_EEcode 
adtX_Vector_resize(
	adt_Container *C, va_list args
) {
	
	
}

adt_EEcode 
adtX_Vector_reserve(
	adt_Container *C, va_list args
) {
	
	
}

adt_EEcode 
adtX_Vector_swap(
	adt_Container *C, adt_Container *O
) {
	
	
}

adt_EEcode 
adtX_Vector_rehash(
	adt_Container *C
) {
	
	
}

adt_EEcode 
adtX_Vector_clear(
	adt_Container *C
) {
	
	
}


/*
 * [ S T A T E ] ===============================================================
 */

void 
adtX_Vector_getoptions(
	adt_Container *C, adt_Options *to
) {
	
	
}

adt_EEcode 
adtX_Vector_getecode(
	adt_Container *C
) {
	
	
}

size_t 
adtX_Vector_getlen(
	adt_Container *C
) {
	
	
}

size_t 
adtX_Vector_getcap(
	adt_Container *C
) {
	
	
}

size_t 
adtX_Vector_getcount(
	adt_Container *C
) {
	
	
}

adt_Value 
adtX_Vector_getkeytype(
	adt_Container *C
) {
	
	
}

adt_Value 
adtX_Vector_getvaluetype(
	adt_Container *C
) {
	
	
}

adt_Value 
adtX_Vector_getdefault(
	adt_Container *C
) {
	
	
}

adt_ECategory*
adtX_Vector_getcategories(
	adt_Container *C, adt_ECategory *list
) {
	
	return list;
}


int 
adtX_Vector_canreserve(
	adt_Container *C
) {
	
	
}

int 
adtX_Vector_canresize(
	adt_Container *C
) {
	
	
}

int 
adtX_Vector_canchange(
	adt_Container *C
) {
	
	
}

int 
adtX_Vector_isempty(
	adt_Container *C
) {
	
	
}

int 
adtX_Vector_isautofree(
	adt_Container *C
) {
	
	
}

int 
adtX_Vector_isautoorder(
	adt_Container *C
) {
	
	
}


adt_Value 
adtX_Vector_setdefault(
	adt_Container *C
) {
	
	
}

adt_EEcode 
adtX_Vector_setimmutable(
	adt_Container *C
) {
	
	
}

int 
adtX_Vector_setresizemult(
	adt_Container *C, size_t mult
) {
	
	
}

adt_EEcode 
adtX_Vector_setautofree(
	adt_Container *C, int flag
) {
	
	
}

adt_EEcode 
adtX_Vector_setautoorder(
	adt_Container *C, int flag
) {
	
	
}

adt_EEcode 
adtX_Vector_sethashf(
	adt_Container *C, adt_FHash hashf
) {
	
	
}

adt_EEcode 
adtX_Vector_setfinalizerf(
	adt_Container *C, adt_FFinalize finalizef
) {
	
	
}

adt_EEcode 
adtX_Vector_setcomparef(
	adt_Container *C, adt_FCompare hashf
) {
	
	
}


/*
 * [ I T E R ] =================================================================
 */

adt_Iterator* 
adtX_Vector_iterator(
	adt_Container *C, adt_EIteratorMode mode, int autofree
) {
	
	
}

adt_Iterator* 
adtX_Vector_iteratorat(
	adt_Container *C, adt_EIteratorMode mode, int autofree, va_list args
) {
	
	
}
