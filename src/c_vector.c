#include "dt.h"

#define ELEMSZ(T) (T.esize * (T.vsize > 1 ? T.vsize : 1))

static const char* dt_vector_name = "dtX_Vector";
static const char* dt_vectoriter_name = "dtX_VectorIter";
static const dt_ENature dt_vector_natures[dt_NAT_MAX] = {
	  dt_NAT_LIST
	, dt_NAT_FLAT
	, dt_NAT_NONE
};

typedef struct dtX_Vector_ dtX_Vector;
typedef struct dtX_VectorIter_ dtX_VectorIter;

struct dtX_Vector_ {

	dt_Ctnr ctnr;

	/* Options */
	dt_Type vtype;
	size_t capmult;
	size_t malign;
	dt_FAlloc allocf;
	void* allocp;
	dt_FEvent eventf;
	void* eventp;

	/* Data */
	size_t cap;
	size_t len;
	void* ptr;
};

struct dtX_VectorIter_ {

	dt_Iter iter;
	dtX_Vector* C;
	int started;
	dt_EIterMode mode;
	size_t pos;
};

static dt_Opts* dtX_Vector_defaultopts(dt_CtnrApi* A, dt_Opts* O);
static const char* dtX_Vector_getimplname(dt_CtnrApi* A);
static size_t dtX_Vector_getbytesize(dt_CtnrApi* A);
static const dt_ENature* dtX_Vector_getnatures(dt_CtnrApi* A);
static dt_Ctnr* dtX_Vector_createwith(dt_CtnrApi* A, dt_Opts *opts);
static dt_EEcode dtX_Vector_dispose(dt_CtnrApi* A, dt_Ctnr* C);
static dt_Ctnr* dtX_Vector_copy(dt_CtnrApi* A, dt_Ctnr* C);
static dt_Opts* dtX_Vector_getopts(dt_CtnrApi* A, dt_Ctnr* C, dt_Opts* opts);
static dt_EEcode dtX_Vector_setopts(dt_CtnrApi* A, dt_Ctnr* C, dt_Opts* S);
static size_t dtX_Vector_has(dt_CtnrApi* A, dt_Ctnr* C, void* k);
static void* dtX_Vector_get(dt_CtnrApi* A, dt_Ctnr* C, void* k);
static dt_EEcode dtX_Vector_put(dt_CtnrApi* A, dt_Ctnr* C, void* k);
static void* dtX_Vector_set(dt_CtnrApi* A, dt_Ctnr* C, void* k, void* v);
static void* dtX_Vector_insert(dt_CtnrApi* A, dt_Ctnr* C, void* k, void* v);
static void* dtX_Vector_remove(dt_CtnrApi* A, dt_Ctnr* C, void* k);
static size_t dtX_Vector_removec(dt_CtnrApi* A, dt_Ctnr* C, void* k, size_t amount);
static dt_EEcode dtX_Vector_sort(dt_CtnrApi* A, dt_Ctnr *C, int reverse);
static dt_EEcode dtX_Vector_reserve(dt_CtnrApi* A, dt_Ctnr *C, size_t size);
static dt_EEcode dtX_Vector_resize(dt_CtnrApi* A, dt_Ctnr *C, size_t size);
static dt_EEcode dtX_Vector_swap(dt_CtnrApi* A, dt_Ctnr *C, dt_Ctnr *O);
static dt_EEcode dtX_Vector_clear(dt_CtnrApi* A, dt_Ctnr *C);
static dt_Iter* dtX_Vector_iterate(dt_CtnrApi* A, dt_Ctnr *C, dt_EIterMode mode);
static dt_Iter* dtX_Vector_iterateat(dt_CtnrApi* A, dt_Ctnr *C, dt_EIterMode mode, void* k);


static size_t dtX_VectorIter_getbytesize(dt_IterApi* A);
static const char* dtX_VectorIter_getctnrapi(dt_IterApi* A);
static dt_EEcode dtX_VectorIter_dispose(dt_IterApi* A, dt_Iter* I);
static void* dtX_VectorIter_actual(dt_IterApi* A, dt_Iter* I);
static void* dtX_VectorIter_actualkeys(dt_IterApi* A, dt_Iter* I);
static void* dtX_VectorIter_next(dt_IterApi* A, dt_Iter* I);
static void* dtX_VectorIter_previous(dt_IterApi* A, dt_Iter* I);
static dt_EIterMode dtX_VectorIter_getmode(dt_IterApi* A, dt_Iter* I);
static int dtX_VectorIter_hasstarted(dt_IterApi* A, dt_Iter* I);
static int dtX_VectorIter_hasnext(dt_IterApi* A, dt_Iter* I);
static int dtX_VectorIter_hasprevious(dt_IterApi* A, dt_Iter* I);
static dt_EEcode dtX_VectorIter_set(dt_IterApi* A, dt_Iter* I, void* v);
static dt_EEcode dtX_VectorIter_remove(dt_IterApi* A, dt_Iter* I);
static int dtX_VectorIter_compare(dt_IterApi* A, dt_Iter* I, dt_Iter* O);


static dt_CtnrApi dt_vector_api_v = {
	  NULL
	, dtX_Vector_getimplname
	, dtX_Vector_getbytesize
	, dtX_Vector_getnatures
	, dtX_Vector_createwith
	, dtX_Vector_dispose
	, dtX_Vector_copy
	, dtX_Vector_defaultopts
	, dtX_Vector_getopts
	, dtX_Vector_setopts
	, dtX_Vector_has
	, dtX_Vector_get
	, dtX_Vector_put
	, dtX_Vector_set
	, dtX_Vector_insert
	, dtX_Vector_remove
	, dtX_Vector_removec
	, NULL /* dtX_Vector_push */
	, NULL /* dtX_Vector_pushr */
	, NULL /* dtX_Vector_pop */
	, NULL /* dtX_Vector_popr */
	, NULL /* dtX_Vector_rot */
	, NULL /* dtX_Vector_rotr */
	, NULL /* dtX_Vector_crot */
	, NULL /* dtX_Vector_crotr */
	, dtX_Vector_sort
	, dtX_Vector_reserve
	, dtX_Vector_resize
	, dtX_Vector_swap
	, NULL /* dtX_Vector_rehash */
	, dtX_Vector_clear
	, dtX_Vector_iterate
	, dtX_Vector_iterateat
};

const dt_CtnrApi* const dt_vector_api = &dt_vector_api_v;

const dt_IterApi dt_vectoriter_api_v = {

	NULL
	, dtX_VectorIter_getbytesize
	, dtX_VectorIter_getctnrapi
	, dtX_VectorIter_dispose
	, dtX_VectorIter_actual
	, dtX_VectorIter_actualkeys
	, dtX_VectorIter_next
	, dtX_VectorIter_previous
	, dtX_VectorIter_getmode
	, dtX_VectorIter_hasstarted
	, dtX_VectorIter_hasnext
	, dtX_VectorIter_hasprevious
	, dtX_VectorIter_set
	, dtX_VectorIter_remove
	, dtX_VectorIter_compare
};


/*##############################################################################
 * [[[   VECTOR   ]]]
 */


/* TODO Tests */
dt_Opts*
dtX_Vector_defaultopts(
	dt_CtnrApi* A, dt_Opts* O
) {

	return dt_defaultopts(O);
}

/* TODO Tests */
const char*
dtX_Vector_getimplname(
	dt_CtnrApi* A
) {

	return dt_vector_name;
}

/* TODO Tests */
size_t
dtX_Vector_getbytesize(
	dt_CtnrApi* A
) {

	return sizeof(dtX_Vector);
}

/* TODO Tests */
const dt_ENature*
dtX_Vector_getnatures(
	dt_CtnrApi* A
) {

	return dt_vector_natures;
}

/* TODO Tests */
size_t
dtX_Vector_getimplhash(
	dt_CtnrApi* A
) {

	return dt_hashstring(dt_vector_name);
}

/* TODO Implementation */
dt_Ctnr*
dtX_Vector_createwith(
	dt_CtnrApi* A, dt_Opts *opts
) {

	int result = 0, retried = 0;
	size_t elemsz = 0;
	dtX_Vector* V = NULL;

startcheck:
	/* Initial allocation */
	if (opts) {
		opts->ecode = dt_OK;
		elemsz = dt_Type_size(opts->vtype);

		if (opts->allocf                     /* Allocator is needed, c'mon... */
				&& opts->vtype               /* Must operate on a type! */
				&& elemsz > 0                /* Size of element must be valid! */
				&& opts->cap >= opts->len) { /* len and cap must be coherent. */

			V = opts->allocf(opts->allocp, NULL, sizeof(dtX_Vector), opts->malign);
			if (!V) {

				/* Allocation will be retried only once. */
				opts->ecode = dt_ERRMEM;
				if (!retried && opts->eventf) {
					result = opts->eventf(opts->eventp, dt_ERRMEM, NULL, NULL, 0, 0);
					if (result >= 0) {
						retried = 1;
						goto startcheck;
					}
				}
			}

		} else
			opts->ecode = dt_ERRMISS;
	}

	if (V) {

		/* Setting options  */
		V->ctnr.ecode = dt_OK;
		V->ctnr.api = dt_vector_api;
		/*
		V->ktype.base = dt_sz_type;
		V->ktype.name = dt_sz_type->name;
		V->ktype.vsize = 1;
		V->ktype.esize = dt_sz_type->esize;
		*/
		V->vtype.base = opts->vtype;
		V->vtype.name = opts->vtype->name;
		V->vtype.vsize = opts->vtype->vsize;
		V->vtype.esize = opts->vtype->esize;
		V->capmult = opts->capmult;
		V->malign = opts->malign;
		V->allocf = opts->allocf;
		V->allocp = opts->allocp;
		V->eventf = opts->eventf;
		V->eventp = opts->eventp;
		V->cap = opts->cap;
		V->len = opts->len;
		V->ptr = NULL;

		retried = 0;
allocptr:
		/* Allocating if needed */
		if (V->cap) {
			V->ptr = V->allocf(V->allocp, NULL, elemsz * V->cap, V->malign);

			if (!V->ptr) {

				/* Allocation will be retried only once. */
				if (!retried && V->eventf) {
					result = V->eventf(V->eventp, dt_ERRMEM, V, NULL, 0, 0);
					if (result >= 0) {
						retried = 1;
						goto allocptr;
					}

				} else {
					/* If it cannot allocate the initial capacity, just
					 * give up on the container.
					 */
					opts->allocf(opts->allocp, V, 0, 0);
					opts->ecode = dt_ERRMEM;
					V = NULL;
				}

			} else {
initvals:
				/* Initialize values, if len > 0 and an initializer
				 * is provided. */
				V->ctnr.ecode = opts->ecode = dt_OK;

				if (V->vtype->vinitf && V->len > 0) {
					result = V->vtype->vinitf(V->vtype->vinitp, 0, &(V->vtype), V->ptr, V->len);

					if (!result) {
						V->ctnr.ecode = opts->ecode = dt_ERRINIT;

						if (V->eventf && !retried) {
							result = V->eventf(V->eventp, dt_ERRMEM, V, NULL, 0, 0);
							if (result >= 0) {
								retried = 1;
								goto initvals;
							}
						}
					}
				}
			}
		}

	}

	return V;
}

/* TODO Implementation */
dt_EEcode
dtX_Vector_dispose(
	dt_CtnrApi* A, dt_Ctnr* C
) {

	dt_EEcode ret = (dt_EEcode)0;
	return ret;
}

/* TODO Implementation */
dt_Ctnr*
dtX_Vector_copy(
	dt_CtnrApi* A, dt_Ctnr* C
) {

	dt_Ctnr* ret = (dt_Ctnr*)0;
	return ret;
}

/* TODO Implementation */
dt_Opts*
dtX_Vector_getopts(
	dt_CtnrApi* A, dt_Ctnr* C, dt_Opts* opts
) {

	dt_Opts* ret = (dt_Opts*)0;
	return ret;
}


/* TODO Implementation */
dt_EEcode
dtX_Vector_setopts(
	dt_CtnrApi* A, dt_Ctnr* C, dt_Opts* opts
) {

	dt_EEcode ret = (dt_EEcode)0;
	return ret;
}

/* TODO Implementation */
size_t
dtX_Vector_has(
	dt_CtnrApi* A, dt_Ctnr* C, void* k
) {

	size_t ret = (size_t)0;
	return ret;
}

/* TODO Implementation */
void*
dtX_Vector_get(
	dt_CtnrApi* A, dt_Ctnr* C, void* k
) {

	void* ret = (void*)0;
	return ret;
}

/* TODO Implementation */
dt_EEcode
dtX_Vector_put(
	dt_CtnrApi* A, dt_Ctnr* C, void* k
) {

	dt_EEcode ret = (dt_EEcode)0;
	return ret;
}

/* TODO Implementation */
void*
dtX_Vector_set(
	dt_CtnrApi* A, dt_Ctnr* C, void* k, void* v
) {

	void* ret = (void*)0;
	return ret;
}

/* TODO Implementation */
void*
dtX_Vector_insert(
	dt_CtnrApi* A, dt_Ctnr* C, void* k, void* v
) {

	void* ret = (void*)0;
	return ret;
}

/* TODO Implementation */
void*
dtX_Vector_remove(
	dt_CtnrApi* A, dt_Ctnr* C, void* k
) {

	void* ret = (void*)0;
	return ret;
}

/* TODO Implementation */
size_t
dtX_Vector_removec(
	dt_CtnrApi* A, dt_Ctnr* C, void* k, size_t amount
) {

	size_t ret = (size_t)0;
	return ret;
}

/* TODO Implementation */
dt_EEcode
dtX_Vector_sort(
	dt_CtnrApi* A, dt_Ctnr *C, int reverse
) {

	dt_EEcode ret = (dt_EEcode)0;
	return ret;
}

/* TODO Implementation */
dt_EEcode
dtX_Vector_reserve(
	dt_CtnrApi* A, dt_Ctnr *C, size_t size
) {

	dt_EEcode ret = (dt_EEcode)0;
	return ret;
}

/* TODO Implementation */
dt_EEcode
dtX_Vector_resize(
	dt_CtnrApi* A, dt_Ctnr *C, size_t size
) {

	dt_EEcode ret = (dt_EEcode)0;
	return ret;
}

/* TODO Implementation */
dt_EEcode
dtX_Vector_swap(
	dt_CtnrApi* A, dt_Ctnr *C, dt_Ctnr *O
) {

	dt_EEcode ret = (dt_EEcode)0;
	return ret;
}

/* TODO Implementation */
dt_EEcode
dtX_Vector_clear(
	dt_CtnrApi* A, dt_Ctnr *C
) {

	dt_EEcode ret = (dt_EEcode)0;
	return ret;
}

/* TODO Implementation */
dt_Iter*
dtX_Vector_iterate(
	dt_CtnrApi* A, dt_Ctnr *C, dt_EIterMode mode
) {

	dt_Iter* ret = (dt_Iter*)0;
	return ret;
}

/* TODO Implementation */
dt_Iter*
dtX_Vector_iterateat(
	dt_CtnrApi* A, dt_Ctnr *C, dt_EIterMode mode, void* k
) {

	dt_Iter* ret = (dt_Iter*)0;
	return ret;
}



/*##############################################################################
 * [[[   ITERATOR   ]]]
 */


/* TODO Implementation */
size_t
dtX_VectorIter_getbytesize(
	dt_IterApi* A
) {

	size_t ret = (size_t)0;
	return ret;
}

/* TODO Implementation */
const dt_CtnrApi*
dtX_VectorIter_getctnrapi(
	dt_IterApi* A
) {

	return dt_vector_api;
}

/* TODO Implementation */
size_t
dtX_VectorIter_getimplhash(
	dt_CtnrApi* A
) {

	size_t ret = (size_t)0;
	return ret;
}

/* TODO Implementation */
dt_EEcode
dtX_VectorIter_dispose(
	dt_IterApi* A, dt_Iter* I
) {

	dt_EEcode ret = (dt_EEcode)0;
	return ret;
}

/* TODO Implementation */
void*
dtX_VectorIter_actual(
	dt_IterApi* A, dt_Iter* I
) {

	void* ret = (void*)0;
	return ret;
}

/* TODO Implementation */
void*
dtX_VectorIter_actualkeys(
	dt_IterApi* A, dt_Iter* I
) {

	void* ret = (void*)0;
	return ret;
}

/* TODO Implementation */
void*
dtX_VectorIter_next(
	dt_IterApi* A, dt_Iter* I
) {

	void* ret = (void*)0;
	return ret;
}

/* TODO Implementation */
void*
dtX_VectorIter_previous(
	dt_IterApi* A, dt_Iter* I
) {

	void* ret = (void*)0;
	return ret;
}

/* TODO Implementation */
dt_EIterMode
dtX_VectorIter_getmode(
	dt_IterApi* A, dt_Iter* I
) {

	dt_EIterMode ret = (dt_EIterMode)0;
	return ret;
}

/* TODO Implementation */
int
dtX_VectorIter_hasstarted(
	dt_IterApi* A, dt_Iter* I
) {

	int ret = (int)0;
	return ret;
}

/* TODO Implementation */
int
dtX_VectorIter_hasnext(
	dt_IterApi* A, dt_Iter* I
) {

	int ret = (int)0;
	return ret;
}

/* TODO Implementation */
int
dtX_VectorIter_hasprevious(
	dt_IterApi* A, dt_Iter* I
) {

	int ret = (int)0;
	return ret;
}

/* TODO Implementation */
dt_EEcode
dtX_VectorIter_set(
	dt_IterApi* A, dt_Iter* I, void* v
) {

	dt_EEcode ret = (dt_EEcode)0;
	return ret;
}

/* TODO Implementation */
dt_EEcode
dtX_VectorIter_remove(
	dt_IterApi* A, dt_Iter* I
) {

	dt_EEcode ret = (dt_EEcode)0;
	return ret;
}

/* TODO Implementation */
int
dtX_VectorIter_compare(
	dt_IterApi* A, dt_Iter* I, dt_Iter* O
) {

	int ret = (int)0;
	return ret;
}

