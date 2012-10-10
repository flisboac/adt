#include "adt/interfaces.h"


const adt_API adt_Api*
adt_getapi(
	adt_Container* C
) {

	const adt_Api *ret = NULL;
	if (C) ret = C->api;
	return ret;
}
