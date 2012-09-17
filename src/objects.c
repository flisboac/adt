#include <stddef.h>
#include "objects.h"

const adtX_ContainerApi* adtX_apis[adt_TYPE_MAX] = {
	  NULL
	, &adtX_api_vector
};
