
#define GETAPI(obj) (obj ? obj -> api : obj)

#define CALL(api, obj, name, args, ok, miss, null) \
	if (api) {\
		/* Tries to find a match for the requested name. */ \
		while (!(api -> name) && api -> base) api = api -> base; \
		/* Executes the method if it's found. */ \
		if (api -> name) { \
			api -> name args; \
			ok; \
		} else { \
			obj -> ecode = dt_ERRSUPP;\
			miss; \
		} \
	} else {\
		obj -> ecode = dt_ERRNULL;\
		null; \
	}

#define CALLECODE(api, obj, name, ret, args, ok, miss, null) \
	if (api) {\
		/* Tries to find a match for the requested name. */ \
		while (!(api -> name) && api -> base) api = api -> base; \
		/* Executes the method if it's found. */ \
		if (api -> name) { \
			ret = api -> name args; \
			ok; \
		} else { \
			ret = obj -> ecode = dt_ERRSUPP;\
			miss; \
		} \
	} else {\
		obj -> ecode = dt_ERRNULL;\
		null; \
	}


#define CALLRET(api, obj, name, ret, args, ok, miss, null) \
	if (api) {\
		/* Tries to find a match for the requested name. */ \
		while (!(api -> name) && api -> base) api = api -> base; \
		/* Executes the method if it's found. */ \
		if (api -> name) { \
			ret = api -> name args; \
			ok; \
		} else { \
			obj -> ecode = dt_ERRSUPP;\
			miss; \
		} \
	} else {\
		obj -> ecode = dt_ERRNULL;\
		null; \
	}

