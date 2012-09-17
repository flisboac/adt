#include <wchar.h>
#include <string.h>
#include "adt/util.h"
#include "objects.h"



int
adt_fitscategory(
    adt_EType ctype, adt_ECategory cat
) {
    
    int valid = 0;
    adt_ECategory category;
    adt_ECategory[] categories;
    
    if (adt_EType_isvalid(ctype) && adt_ECategory_isvalid(cat)) {
        
        categories = adt_getcategoriesfor(ctype);
        do {
            
            if (category == cat) {
                valid = 1;
                break;
            }
        } while (category != adt_CAT_NULL);
    }
    
    return valid;
}


adt_ECategory[]
adt_getcategoriesfor(
    adt_ECtype ctype
) {
    
    adt_ECategory list[] = {adt_CAT_NONE};
    
    if (adt_EType_isvalid(ctype))
        list = adtX_categories[ctype];
    
    return list;
}


adt_Options*
adt_initoptions(
    adt_Options *options
) {
    
    if (options) {
        options->type = adt_TYPE_NONE;
        options->ktype = adtNULL;
        options->vtype = adtNULL;
        options->cap = adtX_DEFAULTCAP;
        options->len = 0;
        options->load = adtX_DEFAULTLOAD;
        options->ctnr = NULL;
        options->from = NULL;
        options->ecode = adt_ECODE_OK;
        options->defaultval = adtNULL;
        options->allocf = realloc;
        options->finalizef = NULL;
        options->hashf = adt_valuehash;
        options->comparef = adt_valuecompare;
        options->resizemult = 2;
        options->immutable = 0;
        options->autofree = 0;
        options->autoorder = 0;
    }
    
    return options;
}


adt_Options*
adt_copyoptions(
    adt_Options *from, adt_Options *to
) {
    
    if (from && to) {
        
        to->type       = from->type;
        to->ktype      = from->ktype;
        to->vtype      = from->vtype;
        to->cap        = from->cap;
        to->len        = from->len;
        to->load       = from->load;
        to->ctnr       = from->ctnr;
        to->from       = from->from;
        to->ecode      = from->ecode;
        to->defaultval = from->defaultval;
        to->allocf     = from->allocf;
        to->finalizef  = from->finalizef;
        to->hashf      = from->hashf;
        to->comparef   = from->comparef;
        to->resizemult = from->resizemult;
        to->immutable  = from->immutable;
        to->autofree   = from->autofree;
        to->autoorder  = from->autoorder;
    }
    
    return to;
}


adt_ECmpResult
adt_valuecompare(
    adt_Value obj, adt_Value other
) {
    
    adt_ECmpResult result = adt_CMP_ERR;
    
    switch (obj.vtype) {
        
        /* Pointer comparisons */
        case adt_VTYPE_CUSTOM:
        case adt_VTYPE_VOIDP:
        case adt_VTYPE_CHARP:
        case adt_VTYPE_WCHARP:
            switch (other.vtype) {
                case adt_VTYPE_CUSTOM:
                case adt_VTYPE_VOIDP:
                case adt_VTYPE_CHARP:
                case adt_VTYPE_WCHARP:
                    if (obj.vp < other.vp)
                        result = adt_CMP_LT;
                    else if (obj.vp == other.vp)
                        result = adt_CMP_EQ;
                    else 
                        result = adt_CMP_GT;
                    break;
            }
            break;
        
        /* Library types' comparisons */
        /* (Not yet implemented!) */
        case adt_VTYPE_CTNR: break;
        case adt_VTYPE_PAIR: break;
        case adt_VTYPE_NODE: break;
        case adt_VTYPE_ITER: break;
        
        /* Boolean comparisons */
        case adt_VTYPE_BOOL:
            if (!obj.b && other.b)
                result = adt_CMP_LT;
            else if (obj.b && !other.b)
                result = adt_CMP_GT;
            else
                result = adt_CMP_EQ;
            break;
        
        /* Number comparisons */
        case adt_VTYPE_CHAR: break;
        case adt_VTYPE_WCHAR: break;
        case adt_VTYPE_SHORT: break;
        case adt_VTYPE_INT: break;
        case adt_VTYPE_LONG: break;
            switch (other.vtype) {
                case adt_VTYPE_CHAR: break;
                case adt_VTYPE_SHORT: break;
                case adt_VTYPE_INT: break;
                case adt_VTYPE_LONG: break;
                    if (obj.l < other.l)
                        result = adt_CMP_LT;
                    else if (obj.l > other.l)
                        result = adt_CMP_GT;
                    else 
                        result = adt_CMP_EQ;
                    break;
            }
            
        case adt_VTYPE_ULONG: break;
        case adt_VTYPE_UCHAR: break;
        case adt_VTYPE_USHORT: break;
        case adt_VTYPE_UINT: break;
            switch (other.vtype) {
                case adt_VTYPE_ULONG: break;
                case adt_VTYPE_UCHAR: break;
                case adt_VTYPE_USHORT: break;
                case adt_VTYPE_UINT: break;
                    if (obj.ul < other.ul)
                        result = adt_CMP_LT;
                    else if (obj.ul > other.ul)
                        result = adt_CMP_GT;
                    else 
                        result = adt_CMP_EQ;
                    break;
            }
            
        case adt_VTYPE_SIZET:
            switch (other.vtype) {
                case adt_VTYPE_SIZET:
                    if (obj.st < other.st)
                        result = adt_CMP_LT;
                    else if (obj.st > other.st)
                        result = adt_CMP_GT;
                    else 
                        result = adt_CMP_EQ;
                    break;
            }
            break;
            
        case adt_VTYPE_PTRDT:
            switch (other.vtype) {
                case adt_VTYPE_PTRDT:
                    if (obj.pd < other.pd)
                        result = adt_CMP_LT;
                    else if (obj.pd > other.pd)
                        result = adt_CMP_GT;
                    else 
                        result = adt_CMP_EQ;
                    break;
            }
            break;
        
        
        /* This is lacking a lot of refinement. Float values deserves
         * a better treatment in comparisons. */
        case adt_VTYPE_FLOAT: break;
        case adt_VTYPE_DOUBLE: break;
        case adt_VTYPE_LDOUBLE: break;
            switch (other.vtype) {
                case adt_VTYPE_FLOAT: break;
                case adt_VTYPE_DOUBLE: break;
                case adt_VTYPE_LDOUBLE: break;
                    if (obj.ld < other.ld)
                        result = adt_CMP_LT;
                    else if (obj.ld > other.ld)
                        result = adt_CMP_GT;
                    else 
                        result = adt_CMP_EQ;
                    break;
            }
            break;
    }
    
    return result;
}


size_t
adt_valuehash(
    adt_Value val
) {
    
    return adt_NOPOS;
}


/* [ M I S C ] ============================================================== */

void
adt_Value_init(
    adt_Value* V
) {
    
    V->vtype = adt_VTYPE_NONE;
    V->vp = NULL;
    V->l = 0L;
    V->ld = 0.0L;
    V->esize = 0;
    V->vsize = 0;
}


/* [ N U L L S ] ============================================================ */


adt_Value
adt_Value_none() {
    
    adt_Value V;
    adt_Value_init(&V);
    return V;
}

adt_Value
adt_Value_end() {
    
    adt_Value V;
    adt_Value_init(&V);
    V.vtype = adt_VTYPE_END;
    return V;
}

/* [ L I B R A R Y  ] ======================================================= */


adt_Value adt_Value_container(
	adt_Container *C
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vsize = 1;
    V.vtype = adt_VTYPE_CTNR;
    
    if (C) {
    	V.ctnr = C;
        switch(C->type) {
            case adt_TYPE_VECTOR: V.ctnr = sizeof(adtX_Vector); break;
        }
    }
	return V;
}

adt_Value adt_Value_pair(
	adt_Pair *P
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vtype = adt_VTYPE_PAIR;
    V.vsize = 1;
    V.esize = sizeof(adt_Pair);
	V.pair = P;
	return V;
}

adt_Value adt_Value_node(
	adt_Node *N
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vtype = adt_VTYPE_NODE;
    V.vsize = 1;
	V.node = N;
	return V;
}

adt_Value adt_Value_iterator(
	adt_Iterator *I
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vsize = 1;
    V.vtype = adt_VTYPE_ITER;
    
    if (I && I->C) {
        V.iter = I;
        switch(I->C->type) {
            case adt_TYPE_VECTOR: V.ctnr = sizeof(adtX_VectorIterator); break;
        }
    }
	return V;
}



/* [ I N T E G E R S  ] ===================================================== */


adt_Value adt_Value_char(
	char c
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vtype = adt_VTYPE_CHAR;
    
	V.c = c;
    V.vsize = 1;
    V.esize = sizeof(char);
	return V;
}

adt_Value adt_Value_uchar(
	unsigned char uc
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vtype = adt_VTYPE_UCHAR;
    
	V.uc = uc;
    V.vsize = 1;
    V.esize = sizeof(unsigned char);
	return V;
}

adt_Value adt_Value_short(
	short int s
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vtype = adt_VTYPE_SHORT;
    
	V.s = s;
    V.vsize = 1;
    V.esize = sizeof(short int);
	return V;
}

adt_Value adt_Value_ushort(
	unsigned short int us
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vtype = adt_VTYPE_USHORT;
    
	V.us = us;
    V.vsize = 1;
    V.esize = sizeof(unsigned short int);
	return V;
}

adt_Value adt_Value_int(
	int i
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vtype = adt_VTYPE_INT;
    
	V.i = i;
    V.vsize = 1;
    V.esize = sizeof(int);
	return V;
}

adt_Value adt_Value_uint(
	unsigned int ui
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vtype = adt_VTYPE_UINT;
    
	V.ui = ui;
    V.vsize = 1;
    V.esize = sizeof(unsigned int);
	return V;
}

adt_Value adt_Value_long(
	long int l
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vtype = adt_VTYPE_LONG;
    
	V.l = l;
    V.vsize = 1;
    V.esize = sizeof(long int);
	return V;
}

adt_Value adt_Value_ulong(
	unsigned long int ul
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vtype = adt_VTYPE_ULONG;
    
	V.ul = ul;
    V.vsize = 1;
    V.esize = sizeof(unsigned long int);
	return V;
}



/* [ F L O A T S  ] ========================================================= */


adt_Value adt_Value_float(
	float f
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vtype = adt_VTYPE_FLOAT;
    
	V.f = f;
    V.vsize = 1;
    V.esize = sizeof(float);
	return V;
}

adt_Value adt_Value_double(
	double d
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vtype = adt_VTYPE_DOUBLE;
    
	V.d = d;
    V.vsize = 1;
    V.esize = sizeof(double);
	return V;
}

adt_Value adt_Value_ldouble(
	long double ld
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vtype = adt_VTYPE_LDOUBLE;
    
	V.ld = ld;
    V.vsize = 1;
    V.esize = sizeof(long double);
	return V;
}



/* [ P O I N T E R S  ] ===================================================== */


adt_Value adt_Value_voidp(
	void *vp
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vtype = adt_VTYPE_VOIDP;
    
    V.vp = vp;
    V.esize = 1;
	return V;
}

adt_Value adt_Value_charp(
	char *cp
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vtype = adt_VTYPE_CHARP;
    
	V.cp = cp;
    V.esize = sizeof(char);
    if (cp) V.vsize = strlen(cp);
	return V;
}

adt_Value adt_Value_wcharp(
	wchar_t wcp
) {
	
	adt_Value V;
	adt_Value_init(&V);
	V.vtype = adt_VTYPE_WCHARP;
    
    V.wcp = wcp;
    V.esize = sizeof(wchar_t);
    if (wcp) V.vsize = wcslen(cp);
	return V;
}



/* [ S T D D E F ] ========================================================== */


adt_Value adt_Value_sizet(
	size_t sz
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vtype = adt_VTYPE_SIZET;
	
    V.sz = sz;
    V.esize = sizeof(size_t);
    V.vsize = 1;
	return V;
}

adt_Value adt_Value_ptrdiff(
	ptrdiff_t pd
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vtype = adt_VTYPE_PTRDT;
	
    V.pd = pd;
    V.esize = sizeof(ptrdiff_t);
    V.vsize = 1;
	return V;
}

adt_Value adt_Value_wchar(
	wchar_t wc
) {
	
	adt_Value V;
	adt_Value_init(&V);
    V.vtype = adt_VTYPE_WCHAR;
	
    V.wc = wc;
    V.esize = sizeof(wchar_t);
    V.vsize = 1;
	return V;
}
