#ifndef ADTX_OBJECTS_H_
#define ADTX_OBJECTS_H_


#include <stddef.h>
#include <stdarg.h>
#include "adtdefs.h"
#include "adt/types.h"

#define adtX_DEFAULTCAP  4
#define adtX_DEFAULTLOAD 10

/*
 * [ A U X I L I A R Y ] =======================================================
 */

typedef struct adtX_SingleBucket_t {
    
    size_t count;
    adt_UValue val;
} adtX_SingleBucket;

typedef struct adtX_PairBucket_t {
    
    size_t count;
    adt_UValue key;
    adt_UValue val;
} adtX_PairBucket;


typedef struct adtX_ContainerApi_t {
    
    /*
     * [ N E W ]
     */
    
    adt_Container *(*new_)(adt_EType ctype, va_list args);
    adt_Container *(*newwith)(adt_Options *options);
    void (*free)(adt_Container *C);
    adt_Container *(*copy)(adt_Container *C);
    
    /*
     * [ A C E S S ]
     */
    
    size_t (*has)(adt_Container *C, va_list args);
    size_t (*hasvalue)(adt_Container *C, va_list args);
    
    adt_Value (*get)(adt_Container *C, va_list args);
    adt_Value (*ocurrences)(adt_Container *C, va_list args);
    adt_Value (*getfirst)(adt_Container *C);
    adt_Value (*getlast)(adt_Container *C);
    
    adt_Value (*set)(adt_Container *C, va_list args);
    
    adt_EEcode (*push)(adt_Container *C, va_list args);
    adt_EEcode (*pushl)(adt_Container *C, va_list args);
    adt_EEcode (*pushr)(adt_Container *C, va_list args);
    adt_Value (*pop)(adt_Container *C);
    adt_Value (*popl)(adt_Container *C);
    adt_Value (*popr)(adt_Container *C);
    
    adt_EEcode (*insert)(adt_Container *C, va_list args);
    adt_Value (*remove)(adt_Container *C, va_list args);
    adt_Value (*removeall)(adt_Container *C, va_list args);
    
    adt_Value (*index)(adt_Container *C, va_list args);
    adt_Value (*rindex)(adt_Container *C, va_list args);
    
    adt_EEcode (*rotl)(adt_Container *C, size_t count); /* Fills with default */
    adt_EEcode (*rotr)(adt_Container *C, size_t count);
    adt_EEcode (*crotl)(adt_Container *C, size_t count); /* Circular shift */
    adt_EEcode (*crotr)(adt_Container *C, size_t count);
    
    /*
     * [ A C T I O N ]
     */
    
    adt_EEcode (*sort)(adt_Container *C);
    adt_EEcode (*resize)(adt_Container *C, va_list args);
    adt_EEcode (*reserve)(adt_Container *C, va_list args);
    adt_EEcode (*swap)(adt_Container *C, adt_Container *O);
    adt_EEcode (*rehash)(adt_Container *C);
    adt_EEcode (*clear)(adt_Container *C);
    
    /*
     * [ S T A T E ]
     */
    
    void (*getoptions)(adt_Container *C, adt_Options *to);
    adt_EEcode (*getecode)(adt_Container *C);
    size_t (*getlen)(adt_Container *C);
    size_t (*getcap)(adt_Container *C);
    size_t (*getcount)(adt_Container *C);
    adt_Value (*getkeytype)(adt_Container *C);
    adt_Value (*getvaluetype)(adt_Container *C);
    adt_Value (*getdefault)(adt_Container *C);
    adt_ECategory *(*getcategories)(adt_Container *C, adt_ECategory* list);
    
    int (*canreserve)(adt_Container *C);
    int (*canresize)(adt_Container *C);
    int (*canchange)(adt_Container *C);
    int (*isempty)(adt_Container *C);
    int (*isautofree)(adt_Container *C);
    int (*isautoorder)(adt_Container *C);
    
    adt_Value (*setdefault)(adt_Container *C);
    adt_EEcode (*setimmutable)(adt_Container *C);
    int (*setresizemult)(adt_Container *C, size_t mult);
    adt_EEcode (*setautofree)(adt_Container *C, int flag);
    adt_EEcode (*setautoorder)(adt_Container *C, int flag);
    adt_EEcode (*sethashf)(adt_Container *C, adt_FHash hashf);
    adt_EEcode (*setfinalizerf)(adt_Container *C, adt_FFinalize finalizef);
    adt_EEcode (*setcomparef)(adt_Container *C, adt_FCompare hashf);
    
    /*
     * [ I T E R ]
     */
    
    adt_Iterator* (*iterator)(adt_Container *C, adt_EIteratorMode mode, int autofree);
    adt_Iterator* (*iteratorat)(adt_Container *C, adt_EIteratorMode mode, int autofree, va_list args);

    /*
     * [ O T H E R S ]
     */
    size_t (*sizeofcontainer)();
    size_t (*sizeofiterator)();
} adtX_ContainerApi;


typedef struct adtX_IteratorApi_t {
    
    adt_EEcode (*setfn)(adt_Iterator *I, adt_FIterate fn, void* state);
    adt_Value (*actual)(adt_Iterator *I);
    adt_Value (*next)(adt_Iterator *I);
    adt_Value (*previous)(adt_Iterator *I);
    int (*hasstarted)(adt_Iterator *I);
    int (*hasnext)(adt_Iterator *I);
    int (*hasprevious)(adt_Iterator *I);
    adt_EIteratorMode (*getmode)(adt_Iterator *I);
    adt_ECmpResult (*compare)(adt_Iterator *I, adt_Iterator *O);
    adt_Container* (*getcontainer)(adt_Iterator *I);
    adt_Value (*getvalue)(adt_Iterator *I);
    adt_EEcode (*getecode)(adt_Iterator *I);
    adt_EEcode (*remove)(adt_Iterator *I);
    adt_EEcode (*setvalue)(adt_Iterator *I, adt_Value val);
    void (*free)(adt_Iterator *I);
} adtX_IteratorApi;

/*
 * [ V A L U E S ] =============================================================
 */

adt_IDATA const adtX_ContainerApi adtX_api_vector;

typedef struct adtX_ContainerBase_t {
    
    adt_Value defaultval;
    adt_EValueType vtype;
    size_t vsize;
    size_t esize;
    adt_FAlloc allocf;
    adt_FFinalize finalizef;
    char immutable;
    size_t resizemult;
    int autofree;
} adtX_ContainerBase;

typedef struct adtX_IteratorBase_t {
    
    int started;
    adt_FIterate fn;
    void* fnstate;
} adtX_IteratorBase;

struct adt_Container_t {
    
    adt_EType type;
    const adtX_ContainerApi *api;
    adt_EEcode ecode;
};

struct adt_Iterator_t {
    
    adt_Container *ctnr;
    adt_EIteratorMode mode;
    const adtX_IteratorApi *api;
    adt_EEcode ecode;
};


/*
 * [ C O N T A I N E R S ] =====================================================
 */


typedef struct adtX_Vector_t {
    
    adt_Container ctnr;
    size_t len;
    size_t cap;
    void *ary;
} adtX_Vector;

typedef struct adtX_VectorIterator_t {
    
    adt_Iterator iter;
    size_t idx;
} adtX_VectorIterator;

adt_IDATA const adtX_ContainerApi* adtX_apis2[adt_TYPE_MAX];

#endif
