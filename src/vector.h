#include "objects.h"

/*
 * [ N E W ] ===================================================================
 */

adt_IAPI adt_Container *adtX_Vector_new(adt_EType ctype, va_list args);
adt_IAPI adt_Container *adtX_Vector_newwith(adt_Options *options);
adt_IAPI void adtX_Vector_free(adt_Container *C);
adt_IAPI adt_Container *adtX_Vector_copy(adt_Container *C);

/*
 * [ A C E S S ] ===============================================================
 */

adt_IAPI size_t adtX_Vector_has(adt_Container *C, va_list args);
adt_IAPI size_t adtX_Vector_hasvalue(adt_Container *C, va_list args);

adt_IAPI adt_Value adtX_Vector_get(adt_Container *C, va_list args);
adt_IAPI size_t adtX_Vector_ocurrences(adt_Container *C, va_list args);
adt_IAPI adt_Value adtX_Vector_getfirst(adt_Container *C);
adt_IAPI adt_Value adtX_Vector_getlast(adt_Container *C);

adt_IAPI adt_Value adtX_Vector_set(adt_Container *C, va_list args);

/* push is pushl */
adt_IAPI adt_EEcode adtX_Vector_pushl(adt_Container *C, va_list args);
adt_IAPI adt_EEcode adtX_Vector_pushr(adt_Container *C, va_list args);
/* pop is popl */
adt_IAPI adt_Value adtX_Vector_popl(adt_Container *C);
adt_IAPI adt_Value adtX_Vector_popr(adt_Container *C);

adt_IAPI adt_EEcode adtX_Vector_insert(adt_Container *C, va_list args);
adt_IAPI adt_Value adtX_Vector_remove(adt_Container *C, va_list args);
adt_IAPI adt_Value adtX_Vector_removeoccurrences(adt_Container *C, va_list args);

adt_IAPI adt_Value adtX_Vector_index(adt_Container *C, va_list args);
adt_IAPI adt_Value adtX_Vector_rindex(adt_Container *C, va_list args);

adt_IAPI adt_EEcode adtX_Vector_rotl(adt_Container *C, size_t count);
adt_IAPI adt_EEcode adtX_Vector_rotr(adt_Container *C, size_t count);
adt_IAPI adt_EEcode adtX_Vector_crotl(adt_Container *C, size_t count);
adt_IAPI adt_EEcode adtX_Vector_crotr(adt_Container *C, size_t count);

/*
 * [ A C T I O N ] =============================================================
 */

adt_IAPI adt_EEcode adtX_Vector_sort(adt_Container *C);
adt_IAPI adt_EEcode adtX_Vector_resize(adt_Container *C, va_list args);
adt_IAPI adt_EEcode adtX_Vector_reserve(adt_Container *C, va_list args);
adt_IAPI adt_EEcode adtX_Vector_swap(adt_Container *C, adt_Container *O);
adt_IAPI adt_EEcode adtX_Vector_rehash(adt_Container *C);
adt_IAPI adt_EEcode adtX_Vector_clear(adt_Container *C);

/*
 * [ S T A T E ] ===============================================================
 */

adt_IAPI void adtX_Vector_getoptions(adt_Container *C, adt_Options *to);
adt_IAPI adt_EEcode adtX_Vector_getecode(adt_Container *C);
adt_IAPI size_t adtX_Vector_getlen(adt_Container *C);
adt_IAPI size_t adtX_Vector_getcap(adt_Container *C);
adt_IAPI size_t adtX_Vector_getcount(adt_Container *C);
adt_IAPI adt_Value adtX_Vector_getkeytype(adt_Container *C);
adt_IAPI adt_Value adtX_Vector_getvaluetype(adt_Container *C);
adt_IAPI adt_Value adtX_Vector_getdefault(adt_Container *C);
adt_IAPI adt_ECategory* adtX_Vector_getcategories(adt_Container *C, adt_ECategory *list);

adt_IAPI int adtX_Vector_canreserve(adt_Container *C);
adt_IAPI int adtX_Vector_canresize(adt_Container *C);
adt_IAPI int adtX_Vector_canchange(adt_Container *C);
adt_IAPI int adtX_Vector_isempty(adt_Container *C);
adt_IAPI int adtX_Vector_isautofree(adt_Container *C);
adt_IAPI int adtX_Vector_isautoorder(adt_Container *C);

adt_IAPI adt_Value adtX_Vector_setdefault(adt_Container *C);
adt_IAPI adt_EEcode adtX_Vector_setimmutable(adt_Container *C);
adt_IAPI adt_EEcode adtX_Vector_setresizemult(adt_Container *C, size_t mult);
adt_IAPI adt_EEcode adtX_Vector_setautofree(adt_Container *C, int flag);
adt_IAPI adt_EEcode adtX_Vector_setautoorder(adt_Container *C, int flag);
adt_IAPI adt_EEcode adtX_Vector_sethashf(adt_Container *C, adt_FHash hashf);
adt_IAPI adt_EEcode adtX_Vector_setfinalizerf(adt_Container *C, adt_FFinalize finalizef);
adt_IAPI adt_EEcode adtX_Vector_setcomparef(adt_Container *C, adt_FCompare hashf);

/*
 * [ I T E R ] =================================================================
 */

adt_IAPI adt_Iterator* adtX_Vector_iterator(adt_Container *C, adt_EIteratorMode mode, int autofree);
adt_IAPI adt_Iterator* adtX_Vector_iteratorat(adt_Container *C, adt_EIteratorMode mode, int autofree, va_list args);
