
#include <stddef.h>
#include "adt/container.h"
#include "adt/interfaces.h"
#include "adt/util.h"

#define GETAPI(C, apiname) C && C->api ? C->api->apiname : NULL

#define DECLCTNR(C) \
	const adt_ContainerApi *ctnrapi = GETAPI(C, ctnr)

#define DECLAPIS(C) \
	DECLCTNR(C); \
	const adt_ListApi *listapi = GETAPI(C, list); \
	const adt_SetApi *setapi = GETAPI(C, set); \
    const adt_MapApi *mapapi = GETAPI(C, map); \
    const adt_BagApi *bagapi = GETAPI(C, bag); \
    const adt_HashableApi *hashapi = GETAPI(C, hash)

#define EXECNORET(C, api, name, args) \
	if (api && api->name) { \
		api->name args; \
	} else { \
		if (C) C->ecode = adt_ERRSUPP; \
	}

#define EXEC(C, api, name, ret, args) \
	if (api && api->name) { \
		ret = api->name args; \
	} else { \
		if (C) C->ecode = adt_ERRSUPP; \
	}

#define EXECECODE(C, api, name, ret, args) \
	if (api && api->name) { \
		ret = api->name args; \
	} else { \
		ret = adt_ERRSUPP; \
		if (C) C->ecode = ret; \
	}


/*
 * [ D I S P O S A L ]
 */


/* TODO Tests */
int
adt_dispose(
	adt_Container *C
) {

	int ret = 0;
	DECLCTNR(C);
	EXEC(C, ctnrapi, dispose, ret, (C));
	return ret;
}

/* TODO Tests */
adt_Container*
adt_copy(
	adt_Container *C
) {

	adt_Container* ret = NULL;
	DECLCTNR(C);
	EXEC(C, ctnrapi, copy, ret, (C));
	return ret;
}



/*
 * [ S T A T E ]
 */


/* TODO Tests */
adt_Options*
adt_getoptions(
	adt_Container *C, adt_Options *opts
) {

	adt_Options* ret = opts;
	DECLCTNR(C);
	EXEC(C, ctnrapi, getoptions, ret, (C, opts));
	return ret;
}

/* TODO Tests */
adt_EEcode
adt_setoptions(
	adt_Container *C, adt_Options *opts
) {

	adt_EEcode  ret = adt_ERROR;
	DECLCTNR(C);
	EXEC(C, ctnrapi, setoptions, ret, (C, opts));
	return ret;
}

/* TODO Tests */
adt_FHash
adt_gethashf(
	adt_Container *C
) {

	adt_FHash ret = NULL;
	DECLAPIS(C);
	EXEC(C, hashapi, gethashf, ret, (C));
	return ret;
}

/* TODO Tests */
int
adt_iscategory(
	adt_Container *C, adt_ECategory cat
) {

	int ret = 0;
	DECLAPIS(C);

	if (C) {
		if (cat == C->cat)
			ret = 1;
		else
			switch(cat) {
			case adt_CAT_LIST:     if (listapi) ret = 1; break;
			case adt_CAT_MAP:      if (mapapi)  ret = 1; break;
			case adt_CAT_SET:      if (setapi)  ret = 1; break;
			case adt_CAT_BAG:      if (bagapi)  ret = 1; break;
			case adt_CAT_HASHABLE: if (hashapi) ret = 1; break;
			}
	}

	return ret;
}

/* TODO Tests */
adt_EEcode
adt_getecode(
	adt_Container *C
) {

	adt_EEcode ret = adt_ERROR;
	if (C) ret = C->ecode;
	return ret;
}

/* TODO Tests */
adt_ECategory
adt_getcategory(
	adt_Container *C
) {

	adt_ECategory ret = adt_CAT_NONE;
	if (C) ret = C->cat;
	return ret;
}

/* TODO Tests */
int*
adt_getcategories(
	adt_Container *C, int* cats
) {

	if (cats && C) {
		cats[adt_CAT_NONE]     = 0;
		cats[adt_CAT_LIST]     = adt_iscategory(C, adt_CAT_LIST);
		cats[adt_CAT_MAP]      = adt_iscategory(C, adt_CAT_MAP);
		cats[adt_CAT_SET]      = adt_iscategory(C, adt_CAT_SET);
		cats[adt_CAT_BAG]      = adt_iscategory(C, adt_CAT_BAG);
		cats[adt_CAT_HASHABLE] = adt_iscategory(C, adt_CAT_HASHABLE);
	}
	return cats;
}

/*
 * [ O P E R A T I O N S ]
 */


/* TODO Tests */
adt_EEcode
adt_sort(
	adt_Container *C, int reverse
) {

	adt_EEcode ret = adt_ERROR;
	DECLCTNR(C);
	EXECECODE(C, ctnrapi, sort, ret, (C, reverse));
	return ret;
}

/* TODO Tests */
adt_EEcode
adt_reserve(
	adt_Container *C, ...
) {

	adt_EEcode ret = adt_ERROR;
	va_list args;
	DECLCTNR(C);

	va_start(args, C);
	EXECECODE(C, ctnrapi, reserve, ret, (C, args));
	va_end(args);

	return ret;
}

/* TODO Tests */
adt_EEcode
adt_resize(
	adt_Container *C, ...
) {

	adt_EEcode ret = adt_ERROR;
	va_list args;
	DECLCTNR(C);

	va_start(args, C);
	EXECECODE(C, ctnrapi, resize, ret, (C, args));
	va_end(args);

	return ret;
}

/* TODO Tests */
adt_EEcode
adt_freeze(
	adt_Container *C
) {

	adt_EEcode ret = adt_ERROR;
	DECLCTNR(C);
	EXECECODE(C, ctnrapi, freeze, ret, (C));
	return ret;
}

/* TODO Tests */
adt_EEcode
adt_swap(
	adt_Container *C, adt_Container *O
) {

	adt_EEcode ret = adt_ERROR;
	DECLCTNR(C);
	EXECECODE(C, ctnrapi, swap, ret, (C, O));
	return ret;
}

/* TODO Tests */
adt_EEcode
adt_clear(
	adt_Container *C
) {

	adt_EEcode ret = adt_ERROR;
	DECLCTNR(C);
	EXECECODE(C, ctnrapi, clear, ret, (C));
	return ret;
}

/* TODO Tests */
adt_EEcode
adt_rehash(
	adt_Container *C
) {

	adt_EEcode ret = adt_ERROR;
	DECLAPIS(C);
	EXECECODE(C, hashapi, rehash, ret, (C));
	return ret;
}



/*
 * [ A C C E S S ]
 */


/* TODO Implementation */
int
adt_has(
	adt_Container *C, ...
) {

	int ret = 0;
	va_list args;
	va_start(args, C);



	va_end(args);
	return ret;
}


/* TODO Implementation */
adt_Value
adt_get(
	adt_Container *C, ...
) {

	adt_Value ret = adtNONE;
	va_list args;
	va_start(args, C);



	va_end(args);
	return ret;
}

/* TODO Implementation */
adt_Value
adt_set(
	adt_Container *C, ...
) {

	adt_Value ret = adtNONE;
	va_list args;
	va_start(args, C);



	va_end(args);
	return ret;
}

/* TODO Implementation */
adt_Value
adt_remove(
	adt_Container *C, ...
) {

	adt_Value ret = adtNONE;
	va_list args;
	va_start(args, C);



	va_end(args);
	return ret;
}

/* TODO Implementation */
adt_Value
adt_insert(
	adt_Container *C, ...
) {

	adt_Value ret = adtNONE;
	va_list args;
	va_start(args, C);



	va_end(args);
	return ret;
}


/* TODO Implementation */
adt_EEcode
adt_pushl(
	adt_Container *C, ...
) {

	adt_EEcode ret = adt_ERROR;
	va_list args;
	va_start(args, C);



	va_end(args);
	return ret;
}

/* TODO Implementation */
adt_EEcode
adt_pushr(
	adt_Container *C, ...
) {

	adt_EEcode ret = adt_ERROR;
	va_list args;
	va_start(args, C);



	va_end(args);
	return ret;
}

/* TODO Implementation */
adt_Value
adt_popl(
	adt_Container *C
) {

	adt_Value ret = adtNONE;
	return ret;
}

/* TODO Implementation */
adt_Value
adt_popr(
	adt_Container *C
) {

	adt_Value ret = adtNONE;
	return ret;
}


/* TODO Implementation */
adt_EEcode
adt_rotl(
	adt_Container *C, size_t count
) {

	adt_EEcode ret = adt_ERROR;
	return ret;
}

/* TODO Implementation */
adt_EEcode
adt_rotr(
	adt_Container *C, size_t count
) {

	adt_EEcode ret = adt_ERROR;
	return ret;
}

/* TODO Implementation */
adt_EEcode
adt_crotl(
	adt_Container *C, size_t count
) {

	adt_EEcode ret = adt_ERROR;
	return ret;
}

/* TODO Implementation */
adt_EEcode
adt_crotr(
	adt_Container *C, size_t count
) {

	adt_EEcode ret = adt_ERROR;
	return ret;
}


/* TODO Implementation */
size_t
adt_getoccurrences(
	adt_Container *C, ...
) {

	size_t ret = 0;
	va_list args;
	va_start(args, C);



	va_end(args);
	return ret;
}

/* TODO Implementation */
adt_Value
adt_removeoccurrences(
	adt_Container *C, size_t amount, ...
) {

	adt_Value ret = adtNONE;
	va_list args;
	va_start(args, amount);



	va_end(args);
	return ret;
}



/*
 * [ I T E R A T O R S ]
 */


/* TODO Implementation */
adt_Iterator*
adt_iterate(
	adt_Container *C, adt_EIteratorMode mode
) {

	adt_Iterator* ret = NULL;
	return ret;
}

/* TODO Implementation */
adt_Iterator*
adt_iterateat(
	adt_Container *C, adt_EIteratorMode mode, ...
) {

	adt_Iterator* ret = NULL;
	va_list args;
	va_start(args, mode);



	va_end(args);
	return ret;
}

/* TODO Implementation */
int
adt_Iterator_dispose(
	adt_Iterator *I
) {

	int ret = 0;
	return ret;
}


/* TODO Implementation */
adt_Value
adt_Iterator_actual(
	adt_Iterator *I
) {

	adt_Value ret = adtNONE;
	return ret;
}

/* TODO Implementation */
adt_Value
adt_Iterator_actualkeys(
	adt_Iterator *I
) {

	adt_Value ret = adtNONE;
	return ret;
}

/* TODO Implementation */
adt_Value
adt_Iterator_next(
	adt_Iterator *I
) {

	adt_Value ret = adtNONE;
	return ret;
}

/* TODO Implementation */
adt_Value
adt_Iterator_previous(
	adt_Iterator *I
) {

	adt_Value ret = adtNONE;
	return ret;
}


/* TODO Implementation */
adt_EIteratorMode
adt_Iterator_getmode(
	adt_Iterator *I
) {

	adt_EIteratorMode ret = adt_ITER_NONE;
	return ret;
}

/* TODO Implementation */
adt_Container*
adt_Iterator_getcontainer(
	adt_Iterator *I
) {

	adt_Container* ret = NULL;
	return ret;
}

/* TODO Implementation */
int
adt_Iterator_hasstarted(
	adt_Iterator *I
) {

	int ret = 0;
	return ret;
}

/* TODO Implementation */
int
adt_Iterator_hasnext(
	adt_Iterator *I
) {

	int ret = 0;
	return ret;
}

/* TODO Implementation */
int
adt_Iterator_hasprevious(
	adt_Iterator *I
) {

	int ret = 0;
	return ret;
}


/* TODO Implementation */
adt_EEcode
adt_Iterator_set(
	adt_Iterator *I, adt_Value val
) {

	adt_EEcode ret = adt_ERROR;
	return ret;
}

/* TODO Implementation */
adt_EEcode
adt_Iterator_remove(
	adt_Iterator *I
) {

	adt_EEcode ret = adt_ERROR;
	return ret;
}

/* TODO Implementation */
adt_EEcode
adt_Iterator_compare(
	adt_Iterator *I, adt_Iterator *O
) {

	adt_EEcode ret = adt_ERROR;
	return ret;
}



