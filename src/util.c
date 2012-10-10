#include "adt/types.h"
#include "adt/util.h"

#define INIT(V) \
	(V).vtype = adt_VTYPE_NONE; \
	(V).esize = 0; \
	(V).vsize = 0; \
	(V).vp = NULL; \
	(V).ul = 0L; \
	(V).ld = 0.0L

/* TODO Implementation */
adt_Options*
adt_defaultoptions(
	adt_Options* O
) {

	adt_Options* ret = ((adt_Options*)0);
	return ret;
}

/* TODO Implementation */
void*
adt_alloc(
	void* state, void* ptr, size_t sz, size_t align
) {

	void* ret = ((void*)0);
	return ret;
}

/* TODO Implementation */
adt_ECmpResult
adt_valuecompare(
	adt_Value obj, adt_Value other
) {

	adt_ECmpResult ret = ((adt_ECmpResult)0);
	return ret;
}

/* TODO Implementation */
size_t
adt_valuehash(
	adt_Value val
) {

	size_t ret = ((size_t)0);
	return ret;
}

/* TODO Tests */
void
adt_Value_init(
	adt_Value* V
) {

	INIT(*V);
}

/* TODO Implementation */
adt_Value
adt_Value_for(
	adt_EValueType vtype
) {

	adt_Value V;
	INIT(V);
	return V;
}



/*
 * [ V A L U E S ]
 */


/* TODO Tests */
adt_Value
adt_Value_none() {

	adt_Value V;
	INIT(V);
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_end() {

	adt_Value V;
	INIT(V);
	V.vtype = adt_VTYPE_END;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_container(
	adt_Container* C
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(adt_Container*);
	V.vsize = 1;
	V.ctnr = C;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_iterator(
	adt_Iterator* I
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(adt_Iterator*);
	V.vsize = 1;
	V.iter = I;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_char(
	char c
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(char);
	V.vsize = 1;
	V.c = c;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_uchar(
	unsigned char uc
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(unsigned char);
	V.vsize = 1;
	V.uc = uc;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_short(
	short int s
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(short int);
	V.vsize = 1;
	V.s = s;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_ushort(
	unsigned short int us
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(unsigned short int);
	V.vsize = 1;
	V.us = us;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_int(
	int i
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(int);
	V.vsize = 1;
	V.i = i;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_uint(
	unsigned int ui
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(unsigned int);
	V.vsize = 1;
	V.ui = ui;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_long(
	long int l
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(long int);
	V.vsize = 1;
	V.l = l;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_ulong(
	unsigned long int ul
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(unsigned long int);
	V.vsize = 1;
	V.ul = ul;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_float(
	float f
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(float);
	V.vsize = 1;
	V.f = f;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_double(
	double d
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(double);
	V.vsize = 1;
	V.d = d;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_ldouble(
	long double ld
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(long double);
	V.vsize = 1;
	V.ld = ld;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_voidp(
	void* vp
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(void*);
	V.vsize = 1;
	V.vp = vp;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_charp(
	char* cp
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(char*);
	V.vsize = 1;
	V.cp = cp;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_wcharp(
	wchar_t* wcp
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(wchar_t*);
	V.vsize = 1;
	V.wcp = wcp;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_sizet(
	size_t sz
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(size_t);
	V.vsize = 1;
	V.sz = sz;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_ptrdiff(
	ptrdiff_t pd
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(ptrdiff_t);
	V.vsize = 1;
	V.pd = pd;
	return V;
}

/* TODO Tests */
adt_Value
adt_Value_wchar(
	wchar_t wc
) {

	adt_Value V;
	INIT(V);
	V.esize = sizeof(wchar_t);
	V.vsize = 1;
	V.wc = wc;
	return V;
}


