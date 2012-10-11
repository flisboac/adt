
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

#define EXECNORET(C, api, name, args, none) \
	if (api && api->name) { \
		api->name args; \
	} else { \
		if (C) C->ecode = adt_ERRSUPP; \
		none; \
	}

#define EXEC(C, api, name, ret, args, none) \
	if (api && api->name) { \
		ret = api->name args; \
	} else { \
		if (C) C->ecode = adt_ERRSUPP; \
		none; \
	}

#define EXECECODE(C, api, name, ret, args, none) \
	if (api && api->name) { \
		ret = api->name args; \
	} else { \
		ret = adt_ERRSUPP; \
		if (C) C->ecode = ret; \
		none; \
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
	EXEC(C, ctnrapi, dispose, ret, (C), {});
	return ret;
}

/* TODO Tests */
adt_Container*
adt_copy(
	adt_Container *C
) {

	adt_Container* ret = NULL;
	DECLCTNR(C);
	EXEC(C, ctnrapi, copy, ret, (C), {});
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
	EXEC(C, ctnrapi, getoptions, ret, (C, opts), {});
	return ret;
}

/* TODO Tests */
adt_EEcode
adt_setoptions(
	adt_Container *C, adt_Options *opts
) {

	adt_EEcode  ret = adt_ERROR;
	DECLCTNR(C);
	EXEC(C, ctnrapi, setoptions, ret, (C, opts), {});
	return ret;
}

/* TODO Tests */
adt_FHash
adt_gethashf(
	adt_Container *C
) {

	adt_FHash ret = NULL;
	DECLAPIS(C);
	EXEC(C, hashapi, gethashf, ret, (C), {});
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


adt_Value
adt_getdefault(
	adt_Container* C
) {

	adt_Value V = adtNONE;
	adt_Options opts;
	DECLCTNR(C);
	EXECNORET(C, ctnrapi, getoptions, (C, &opts), {});
	if (C && C->ecode == adt_OK) V = opts.defaultval;
	return V;
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
	EXECECODE(C, ctnrapi, sort, ret, (C, reverse), {});
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
	EXECECODE(C, ctnrapi, reserve, ret, (C, args), {});
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
	EXECECODE(C, ctnrapi, resize, ret, (C, args), {});
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
	EXECECODE(C, ctnrapi, freeze, ret, (C), {});
	return ret;
}

/* TODO Tests */
adt_EEcode
adt_swap(
	adt_Container *C, adt_Container *O
) {

	adt_EEcode ret = adt_ERROR;
	DECLCTNR(C);
	EXECECODE(C, ctnrapi, swap, ret, (C, O), {});
	return ret;
}

/* TODO Tests */
adt_EEcode
adt_clear(
	adt_Container *C
) {

	adt_EEcode ret = adt_ERROR;
	DECLCTNR(C);
	EXECECODE(C, ctnrapi, clear, ret, (C), {});
	return ret;
}

/* TODO Tests */
adt_EEcode
adt_rehash(
	adt_Container *C
) {

	adt_EEcode ret = adt_ERROR;
	DECLAPIS(C);
	EXECECODE(C, hashapi, rehash, ret, (C), {});
	return ret;
}



/*
 * [ A C C E S S ]
 */


/* TODO Tests */
int
adt_has(
	adt_Container *C, ...
) {

	int ret = 0;
	va_list args;
	DECLAPIS(C);

	va_start(args, C);
	if (C)
		switch (C->cat) {
		case adt_CAT_LIST: EXEC(C, listapi, has, ret, (C, args), {}); break;
		case adt_CAT_SET:  EXEC(C, setapi,  has, ret, (C, va_arg(args, adt_Value)), {}); break;
		case adt_CAT_MAP:  EXEC(C, mapapi,  has, ret, (C, args), {}); break;
		default:           C->ecode = adt_ERRSUPP; break;
		}
	va_end(args);

	return ret;
}


/* TODO Tests */
adt_Value
adt_get(
	adt_Container *C, ...
) {

	adt_Value ret = adtNONE;
	va_list args;
	DECLAPIS(C);

	va_start(args, C);
	if (C)
		switch (C->cat) {
		case adt_CAT_LIST: EXEC(C, listapi, get, ret, (C, args), {}); break;
		case adt_CAT_MAP:  EXEC(C, mapapi,  get, ret, (C, args), {}); break;
		default:           C->ecode = adt_ERRSUPP; break;
		}
	va_end(args);

	return ret;
}

/* TODO Tests */
adt_Value
adt_set(
	adt_Container *C, ...
) {

	adt_Value ret = adtNONE;
	va_list args;
	adt_Value V;
	DECLAPIS(C);

	va_start(args, C);
	if (C) {
		V = va_arg(args, adt_Value);

		switch (C->cat) {
		case adt_CAT_LIST: EXEC(C, listapi, set, ret, (C, V, args), {}); break;
		case adt_CAT_SET:  EXEC(C, setapi,  set, ret, (C, V), {}); break;
		case adt_CAT_MAP:  EXEC(C, mapapi,  set, ret, (C, V, args), {}); break;
		default:           C->ecode = adt_ERRSUPP; break;
		}
	}
	va_end(args);

	return ret;
}

/* TODO Tests */
adt_Value
adt_remove(
	adt_Container *C, ...
) {

	adt_Value ret = adtNONE;
	va_list args;
	DECLAPIS(C);

	va_start(args, C);
	if (C)
		switch (C->cat) {
		case adt_CAT_LIST: EXEC(C, listapi, remove, ret, (C, args), {}); break;
		case adt_CAT_SET:  EXEC(C, setapi,  remove, ret, (C, va_arg(args, adt_Value)), {}); break;
		case adt_CAT_MAP:  EXEC(C, mapapi,  remove, ret, (C, args), {}); break;
		default:           C->ecode = adt_ERRSUPP; break;
		}
	va_end(args);

	return ret;
}

/* TODO Tests */
adt_Value
adt_insert(
	adt_Container *C, ...
) {

	adt_Value ret = adtNONE;
	va_list args;
	adt_Value V;
	DECLAPIS(C);

	va_start(args, C);
	V = va_arg(args, adt_Value);
	EXEC(C, listapi, insert, ret, (C, V, args), {});
	va_end(args);

	return ret;
}


/* TODO Tests */
adt_EEcode
adt_pushl(
	adt_Container *C, ...
) {

	adt_EEcode ret = adt_ERROR;
	va_list args;
	adt_Value V;
	DECLAPIS(C);

	va_start(args, C);
	V = va_arg(args, adt_Value);
	EXECECODE(C, listapi, pushl, ret, (C, V), {});
	va_end(args);

	return ret;
}

/* TODO Tests */
adt_EEcode
adt_pushr(
	adt_Container *C, ...
) {

	adt_EEcode ret = adt_ERROR;
	va_list args;
	adt_Value V;
	DECLAPIS(C);

	va_start(args, C);
	V = va_arg(args, adt_Value);
	EXECECODE(C, listapi, pushr, ret, (C, V), {});
	va_end(args);

	return ret;
}

/* TODO Tests */
adt_Value
adt_popl(
	adt_Container *C
) {

	adt_Value ret = adtNONE;
	adt_Value V;
	DECLAPIS(C);
	EXEC(C, listapi, popl, ret, (C), {});
	return ret;
}

/* TODO Tests */
adt_Value
adt_popr(
	adt_Container *C
) {

	adt_Value ret = adtNONE;
	adt_Value V;
	DECLAPIS(C);
	EXEC(C, listapi, popr, ret, (C), {});
	return ret;
}


/* TODO Tests */
size_t
adt_rotl(
	adt_Container *C, size_t count
) {

	adt_Value V;
	adt_Value D = adt_getdefault(C);
	size_t i;
	DECLAPIS(C);
	EXEC(C, listapi, popr, i, (C, count), {
		for (i = 0; i < count; ++i) {
			V = adt_popl(C);
			if (adt_OK != C->ecode) break;
			C->ecode = adt_pushr(C, D);
			if (adt_OK != C->ecode) break;
		}
	});
	return i;
}

/* TODO Tests */
size_t
adt_rotr(
	adt_Container *C, size_t count
) {

	adt_Value V;
	adt_Value D = adt_getdefault(C);
	size_t i;
	DECLAPIS(C);
	EXEC(C, listapi, popr, i, (C, count), {
		for (i = 0; i < count; ++i) {
			V = adt_popr(C);
			if (adt_OK != C->ecode) break;
			C->ecode = adt_pushl(C, D);
			if (adt_OK != C->ecode) break;
		}
	});
	return i;
}

/* TODO Tests */
size_t
adt_crotl(
	adt_Container *C, size_t count
) {

	adt_EEcode ret = adt_ERROR;
	adt_Value V;
	size_t i;
	DECLAPIS(C);
	EXEC(C, listapi, popr, i, (C, count), {
		for (i = 0; i < count; ++i) {
			V = adt_popl(C);
			if (adt_OK != C->ecode) break;
			C->ecode = adt_pushr(C, V);
			if (adt_OK != C->ecode) break;
		}
	});
	return i;
	return ret;
}

/* TODO Tests */
size_t
adt_crotr(
	adt_Container *C, size_t count
) {

	adt_Value V;
	size_t i;
	DECLAPIS(C);
	EXEC(C, listapi, popr, i, (C, count), {
		for (i = 0; i < count; ++i) {
			V = adt_popr(C);
			if (adt_OK != C->ecode) break;
			C->ecode = adt_pushl(C, V);
			if (adt_OK != C->ecode) break;
		}
	});
	return i;
}


/* TODO Tests */
size_t
adt_getoccurrences(
	adt_Container *C, ...
) {

	size_t ret = 0;
	int haskey = 0;
	va_list args;
	DECLAPIS(C);

	va_start(args, C);
	EXEC(C, bagapi, getoccurrences, ret, (C, args), {
		if (C)
			switch (C->cat) {
			case adt_CAT_LIST: EXEC(C, listapi, has, haskey, (C, args), {}); break;
			case adt_CAT_SET:  EXEC(C, setapi,  has, haskey, (C, va_arg(args, adt_Value)), {}); break;
			case adt_CAT_MAP:  EXEC(C, mapapi,  has, haskey, (C, args), {}); break;
			default:           C->ecode = adt_ERRSUPP; break;
			}
		if (haskey) ret = 1;
	});
	va_end(args);

	return ret;
}

/* TODO Tests */
size_t
adt_removeoccurrences(
	adt_Container *C, size_t amount, ...
) {

	adt_Value ret = adtNONE;
	size_t i = 0;
	int flag = 0;
	va_list args;
	DECLAPIS(C);

	if (bagapi && bagapi->removeoccurrences) {

		va_start(args, amount);
		i = bagapi->removeoccurrences(C, amount, args);
		va_end(args);
	} else {

		if (C) {
			/* Supposed to succeed unless stated otherwise. */
			C->ecode = adt_OK;

			/* This loop will probably be run only once. */
			for(i = 0; i < amount; i++) {
				flag = 0;

				/* Check if there's a key in the container in the index passed. */
				va_start(args, amount);
				switch (C->cat) {
				case adt_CAT_LIST: EXEC(C, listapi, has, flag, (C, args), {}); break;
				case adt_CAT_SET:  EXEC(C, setapi,  has, flag, (C, va_arg(args, adt_Value)), {}); break;
				case adt_CAT_MAP:  EXEC(C, mapapi,  has, flag, (C, args), {}); break;
				}
				va_end(args);

				/* If there is, remove it. */
				if (flag) {

					/* First, try to remove. */
					flag = 0;
					va_start(args, amount);
					switch (C->cat) {
					case adt_CAT_LIST: EXEC(C, listapi, remove, flag, (C, args), {}); break;
					case adt_CAT_SET:  EXEC(C, setapi,  remove, flag, (C, va_arg(args, adt_Value)), {}); break;
					case adt_CAT_MAP:  EXEC(C, mapapi,  remove, flag, (C, args), {}); break;
					}
					va_end(args);

					/* If the removal was not successful, break and exit.
					 * C->ecode is supposed to hold the reason. */
					if (!flag) break;

				/* Else, just break. All occurrences were already removed.
				 * If any error has ourred  while checking for the existence of
				 * the key, the reason will be in C->ecode. */
				} else
					break;
			}
		}
	}

	return i;
}


/*
 * [ I T E R A T O R S ]
 */


/* TODO Tests */
adt_Iterator*
adt_iterate(
	adt_Container *C, adt_EIteratorMode mode
) {

	adt_Iterator* ret = NULL;
	DECLCTNR(C);
	EXEC(C, ctnrapi, iterate, ret, (C, mode), {});
	return ret;
}

/* TODO Tests */
adt_Iterator*
adt_iterateat(
	adt_Container *C, adt_EIteratorMode mode, ...
) {

	adt_Iterator* ret = NULL;
	va_list args;
	DECLCTNR(C);

	va_start(args, mode);
	EXEC(C, ctnrapi, iterateat, ret, (C, mode, args), {});
	va_end(args);

	return ret;
}

/* TODO Tests */
int
adt_Iterator_dispose(
	adt_Iterator *I
) {

	int ret = 0;
	const adt_IteratorApi* iterapi = I ? I->api : NULL;
	EXEC(I, iterapi, dispose, ret, (I), {});
	return ret;
}


/* TODO Tests */
adt_Value
adt_Iterator_actual(
	adt_Iterator *I
) {

	adt_Value ret = adtNONE;
	const adt_IteratorApi* iterapi = I ? I->api : NULL;
	EXEC(I, iterapi, actual, ret, (I), {});
	return ret;
}

/* TODO Tests */
adt_Value
adt_Iterator_actualkeys(
	adt_Iterator *I
) {

	adt_Value ret = adtNONE;
	const adt_IteratorApi* iterapi = I ? I->api : NULL;
	EXEC(I, iterapi, actualkeys, ret, (I), {});
	return ret;
}

/* TODO Tests */
adt_Value
adt_Iterator_next(
	adt_Iterator *I
) {

	adt_Value ret = adtNONE;
	const adt_IteratorApi* iterapi = I ? I->api : NULL;
	EXEC(I, iterapi, next, ret, (I), {});
	return ret;
}

/* TODO Tests */
adt_Value
adt_Iterator_previous(
	adt_Iterator *I
) {

	adt_Value ret = adtNONE;
	const adt_IteratorApi* iterapi = I ? I->api : NULL;
	EXEC(I, iterapi, previous, ret, (I), {});
	return ret;
}


/* TODO Tests */
adt_EIteratorMode
adt_Iterator_getmode(
	adt_Iterator *I
) {

	adt_EIteratorMode ret = adt_ITER_NONE;
	if (I) ret = I->mode;
	return ret;
}

/* TODO Tests */
adt_EEcode
adt_Iterator_getecode(
	adt_Iterator *I
) {

	adt_EEcode ret = adt_ERROR;
	if (I) ret = I->ecode;
	return ret;
}

/* TODO Tests */
int
adt_Iterator_getautofree(
	adt_Iterator* I
) {

	int ret = 0;
	if (I) ret = I->autofree;
	return ret;
}

/* TODO Tests */
adt_Container*
adt_Iterator_getcontainer(
	adt_Iterator *I
) {

	adt_Container* ret = NULL;
	const adt_IteratorApi* iterapi = I ? I->api : NULL;
	EXEC(I, iterapi, getcontainer, ret, (I), {});
	return ret;
}

/* TODO Tests */
int
adt_Iterator_hasstarted(
	adt_Iterator *I
) {

	int ret = 0;
	const adt_IteratorApi* iterapi = I ? I->api : NULL;
	EXEC(I, iterapi, hasstarted, ret, (I), {});
	return ret;
}

/* TODO Tests */
int
adt_Iterator_hasnext(
	adt_Iterator *I
) {

	int ret = 0;
	const adt_IteratorApi* iterapi = I ? I->api : NULL;
	EXEC(I, iterapi, hasnext, ret, (I), {});
	return ret;
}

/* TODO Tests */
int
adt_Iterator_hasprevious(
	adt_Iterator *I
) {

	int ret = 0;
	const adt_IteratorApi* iterapi = I ? I->api : NULL;
	EXEC(I, iterapi, hasprevious, ret, (I), {});
	return ret;
}


/* TODO Tests */
adt_EEcode
adt_Iterator_set(
	adt_Iterator *I, adt_Value val
) {

	adt_EEcode ret = adt_ERROR;
	const adt_IteratorApi* iterapi = I ? I->api : NULL;
	EXECECODE(I, iterapi, set, ret, (I, val), {});
	return ret;
}

/* TODO Tests */
adt_EEcode
adt_Iterator_remove(
	adt_Iterator *I
) {

	adt_EEcode ret = adt_ERROR;
	const adt_IteratorApi* iterapi = I ? I->api : NULL;
	EXECECODE(I, iterapi, remove, ret, (I), {});
	return ret;
}

/* TODO Tests */
adt_EEcode
adt_Iterator_compare(
	adt_Iterator *I, adt_Iterator *O
) {

	adt_EEcode ret = adt_ERROR;
	const adt_IteratorApi* iterapi = I ? I->api : NULL;
	EXECECODE(I, iterapi, compare, ret, (I, O), {});
	return ret;
}



