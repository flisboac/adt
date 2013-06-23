
/*

dtc  - ctnr
dte  - elem
dti  - iter
dta  - api
dto  - opts
dtst - state

dtv  - vector
dtd  - deque
dtl  - list
dtfl - flist
dts  - treeset
dtm  - treemap
dtb  - bitvector
dths - hashset
dthm - hashmap

dtq  - queue
dtpq - pqueue
dtst - stack
dtt  - tree
dtg  - graph

*/

typedef size_t    (*dt_FHash)  (void* a);
typedef int       (*dt_FCmp)   (dt_EEcode outcome, void* a, void* b);
typedef dt_EEcode (*dt_FValue) (void* valuep, int what, size_t elemsz, void* obj, void* to);

typedef void* (*dt_FAlloc) (void* allocp, int reason, void* ptr, size_t sz);
typedef int   (*dt_FEvent) ()

typedef struct dt_Type_ {

    size_t   len;
	dt_Elem* ptr;
} dt_Type_;

typedef struct dt_Elem_ {


} dt_Elem;



typedef struct dt_CtnrApi_ {

	dt_CtnrApi* base;
	const char* name;
	size_t      size;
	dt_Opts*    opts;
	dt_ENature* natures;
	
} dt_CtnrApi;


typedef struct dt_Ctnr_ {

	dt_CtnrApi* api;
	dt_EEcode   ecode;
} dt_Ctnr;

/* TYPE */


#define dt_TypeT(TN) dt_Type__ ## TN ## __type

#define dt_TypeT_DECL(TN) \
	typedef struct dt_TypeT(TN) ## _ {
		dt_Type*  base;
		size_t    size;
		dt_FCmp   cmpf;
		dt_FHash  hashf;
		dt_FValue valuef;
		void*     valuep;
	} dt_TypeT(TN)

#define dt_TypeT_DEFN(TN) \



/* RAW TYPE (RV = Raw type for value) */


#define dt_VectorRV(TN) dt_Vector__ ## TN ## __value_rawtype

#define dt_VectorRV_DECL(TN, T) \
	typedef T TN


/* DATA TYPE (D) */


#define dt_VectorD(TN) dt_Vector__ ## TN ## __data

#define dt_VectorD_DECL(TN) \
	typedef struct dt_VectorD(TN) dt_VectorD(TN)

#define dt_Vector_DEFN(TN)    \
	struct dt_VectorD(TN) {   \
                              \
		size_t           len; \
		size_t           cap; \
		dt_VectorRV(TN)* ptr; \
	}


/* API TYPE (A) */


#define dt_VectorA(TN) dt_Vector__ ## TN ## __api

#define dt_VectorA_DECL(TN) \
	typedef dt_VectorA(TN) dt_VectorA(TN)

#define dt_VectorA_DEFN(TN) \
	struct dt_VectorA(TN) {

	}


/* CONTAINER (C) */


#define dt_VectorC(TN) dt_Vector__ ## TN ## __ctnr

#define dt_VectorC_DECL(TN) \
	typedef struct dt_VectorC(TN) dt_VectorC(TN)

#define dt_VectorC_DEFN(TN) \
	struct dt_VectorC(TN) { \
		dt_Ctnr base; \
		dt_VectorD(RT) data; \
	}


/* ALL-IN-ONE */

#define dt_Vector_DECL(name, T)


typedef struct dt_Vector_ {
	

} dt_Vector; 