#include <stddef.h>
#include "objects.h"

const adtX_ContainerApi** adtX_apis() {

	static const adtX_ContainerApi* apis[adt_TYPE_MAX];
	int i = 0;
	apis[i++] = NULL;
	apis[i++] = (const adtX_ContainerApi*)&adtX_api_vector;

	return apis;
}