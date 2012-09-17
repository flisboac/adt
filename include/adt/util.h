#ifndef ADT_UTIL_H_
#define

#include "adtdefs.h"
#include "adt/types.h"

/**
 * @}
 * @ingroup adt_util_misc
 * @{
 */

adt_API int adt_fitscategory(adt_EType ctype, adt_ECategory cat);
adt_API adt_ECategory[] adt_getcategoriesfor(adt_ECtype ctype);
adt_API adt_Options* adt_initoptions(adt_Options *options);
adt_API adt_Options* adt_copyoptions(adt_Options *from, adt_Options *to);
adt_API adt_ECmpResult adt_valuecompare(adt_Value obj, adt_Value other);
adt_API size_t adt_valuehash(adt_Value val);


/**
 * @}
 * @ingroup adt_util_val
 * @{
 */

adt_API void adt_Value_init(adt_Value* V);
adt_API adt_Value adt_Value_none();
adt_API adt_Value adt_Value_end();
#define adtNONE adt_Value_none()
#define adtEND adt_Value_end()

adt_API adt_Value adt_Value_container(adt_Container *C);
adt_API adt_Value adt_Value_pair(adt_Pair *P);
adt_API adt_Value adt_Value_node(adt_Node *N);
adt_API adt_Value adt_Value_iterator(adt_Iterator *I);
#define adtCTNR(C) adt_Value_container(C)
#define adtPAIR(P) adt_Value_pair(P)
#define adtNODE(N) adt_Value_node(N)
#define adtITER(I) adt_Value_iterator(I)

adt_API adt_Value adt_Value_char(char c);
adt_API adt_Value adt_Value_uchar(unsigned char uc);
adt_API adt_Value adt_Value_short(short int s);
adt_API adt_Value adt_Value_ushort(unsigned short int us);
adt_API adt_Value adt_Value_int(int i);
adt_API adt_Value adt_Value_uint(unsigned int ui);
adt_API adt_Value adt_Value_long(long int l);
adt_API adt_Value adt_Value_ulong(unsigned long int ul);
#define adtC(x) adt_Value_char(x)
#define adtUC(x) adt_Value_uchar(x)
#define adtS(x) adt_Value_short(x)
#define adtUS(x) adt_Value_ushort(x)
#define adtI(x) adt_Value_int(x)
#define adtUI(x) adt_Value_uint(x)
#define adtL(x) adt_Value_long(x)
#define adtUL(x) adt_Value_ulong(x)

adt_API adt_Value adt_Value_float(float f);
adt_API adt_Value adt_Value_double(double d);
adt_API adt_Value adt_Value_ldouble(long double ld);
#define adtF(x) adt_Value_float(x)
#define adtD(x) adt_Value_double(x)
#define adtLD(x) adt_Value_ldouble(x)

adt_API adt_Value adt_Value_voidp(void *vp);
adt_API adt_Value adt_Value_charp(char *cp);
adt_API adt_Value adt_Value_wcharp(wchar_t wcp);
#define adtVP(x) adt_Value_voidp(x)
#define adtCP(x) adt_Value_charp(x)
#define adtWP(x) adt_Value_wcharp(x)
#define adtNULL adtVP(NULL)

adt_API adt_Value adt_Value_sizet(size_t sz);
adt_API adt_Value adt_Value_ptrdiff(ptrdiff_t pd);
adt_API adt_Value adt_Value_wchar(wchar_t wc);
#define adtSZ(x) adt_Value_sizet(x)
#define adtPD(x) adt_Value_ptrdiff(x)
#define adtW(x) adt_Value_wchar(x)

#define adt1() adtI(1)
#define adt0() adtI(0)

#endif
