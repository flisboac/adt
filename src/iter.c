#include "dt.h"
#include "macros.h"

#define DECLITERAPI(obj) \
	dt_IterApi* api = GETAPI(obj)

/* TODO Implementation */
dt_EEcode
dt_idispose(
	dt_Iter* I
) {

	dt_EEcode ret = dt_ERROR;
	DECLITERAPI(I);
	CALLECODE(api, I, dispose, ret, (api, I), {}, {}, {});
	return ret;
}

/* TODO Implementation */
void*
dt_iactual(
	dt_Iter* I
) {

	void* ret = NULL;
	DECLITERAPI(I);
	CALLRET(api, I, actual, ret, (api, I), {}, {}, {});
	return ret;
}

/* TODO Implementation */
void*
dt_ikeys(
	dt_Iter* I
) {

	void* ret = NULL;
	DECLITERAPI(I);
	CALLRET(api, I, actualkeys, ret, (api, I), {}, {}, {});
	return ret;
}

/* TODO Implementation */
void*
dt_inext(
	dt_Iter* I
) {

	void* ret = NULL;
	DECLITERAPI(I);
	CALLRET(api, I, next, ret, (api, I), {}, {}, {});
	return ret;
}

/* TODO Implementation */
void*
dt_iprev(
	dt_Iter* I
) {

	void* ret = NULL;
	DECLITERAPI(I);
	CALLRET(api, I, previous, ret, (api, I), {}, {}, {});
	return ret;
}

/* TODO Implementation */
int
dt_istarted(
	dt_Iter* I
) {

	int ret = 0;
	DECLITERAPI(I);
	CALLRET(api, I, hasstarted, ret, (api, I), {}, {}, {});
	return ret;
}

/* TODO Implementation */
int
dt_ihasnext(
	dt_Iter* I
) {

	int ret = 0;
	DECLITERAPI(I);
	CALLRET(api, I, hasnext, ret, (api, I), {}, {}, {});
	return ret;
}

/* TODO Implementation */
int
dt_ihasprev(
	dt_Iter* I
) {

	int ret = 0;
	DECLITERAPI(I);
	CALLRET(api, I, hasprevious, ret, (api, I), {}, {}, {});
	return ret;
}

/* TODO Implementation */
dt_EEcode
dt_iset(
	dt_Iter* I, void* v
) {

	dt_EEcode ret = dt_ERROR;
	DECLITERAPI(I);
	CALLECODE(api, I, set, ret, (api, I, v), {}, {}, {});
	return ret;
}

/* TODO Implementation */
dt_EEcode
dt_iremove(
	dt_Iter* I
) {

	dt_EEcode ret = dt_ERROR;
	DECLITERAPI(I);
	CALLECODE(api, I, remove, ret, (api, I), {}, {}, {});
	return ret;
}

/* TODO Implementation */
int
dt_icompare(
	dt_Iter* I, dt_Iter* O
) {

	int ret = dt_NOCMP;
	DECLITERAPI(I);
	CALLRET(api, I, compare, ret, (api, I, O), {}, {}, {});
	return ret;
}


