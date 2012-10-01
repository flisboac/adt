#ifndef ADT_INTERFACES_H_
#define ADT_INTERFACES_H_

#include <stdarg.h>
#include "adtdef.h"
#include "adt/types.h"

typedef struct adt_Api_t adt_Api;

/*
 * Data Access APIs.
 * These API's implement what the Container API doesn't, the data access
 * model. 
 */
typedef struct adt_ListApi_t adt_ListApi;
typedef struct adt_SetApi_t adt_SetApi;
typedef struct adt_MapApi_t adt_MapApi;

/*
 * Trait APIs.
 * These APIs represent (and implement) a specific behaviour or
 * characteristic of the container. They do not provide direct means to data
 * access.
 */
typedef struct adt_BagApi_t adt_BagApi;
typedef struct adt_HashableApi_t adt_HashableApi;


struct adt_Api_t {
    
    adt_ContainerApi *ctnr;
    adt_ListApi *list;
    adt_SetApi *set;
    adt_MapApi *map;
    adt_BagApi *bag;
    adt_HashableApi *hash;
};

struct adt_Container_t {
    
    /*
     * A pointer to the array of API's supported by this container.
     * It must have at least one data access API to be actually usable.
     */
    adt_Api api;
    
    /*
     * Stores the last error ocurred when using the container.
     */
    adt_EEcode ecode;
    
    /*
     * This is the container's original implementation.
     * This value is merely informative, and is ignored by the front-end API.
     * It may make no sense for user-supplied types.
     */
    adt_EType type;
    
    /*
     * This is the primary category for the container.
     * This field is used to determine which API to use in case of ambiguities
     * regarding data access, because a container may have other types.
     */
    adt_ECategory cat;
    
    /*
     * If the user sets this flag to true, on the next call to any of the
     * frontend's methods, the container will be freed.
     */
    int autofree;
};

struct adt_Iterator_t {
    
    adt_IteratorApi *api;
    adt_FIterate fn;
    void *fnstate;
    adt_EEcode ecode;
    int autofree;
};

struct adt_ContainerApi_t {
    
    /* 
     * General data about the implementation.
     */
    
    const char* (*implname)();
    size_t (*sizeofcontainer)();
    adt_Options* (*defaultoptions)(adt_Options* opts);
    
    /*
     * Container creation and disposal.
     */
    
    adt_Container* (*create)();
    adt_Container* (*createwith)(adt_Options *opts);
    int (*dispose)(adt_Container *C);
    adt_Container* (*copy)(adt_Container *C);
    
    /*
     * Container state.
     * To get the container's data, use getoptions(), and from the
     * returned data, change whatever you want to configure in the container
     * and pass that altered data to setoptions(). Any differing option will
     * be applied. An error interrupts the process, but don't revert
     * previous successful changes.
     */
    
    adt_Options* (*getoptions)(adt_Container *C, adt_Options *opts);
    adt_EEcode (*setoptions)(adt_Container *C, adt_Options *opts);
    
    /*
     * Container operations.
     * Some containers may need special procedures for some state changes.
     * Things like resizing, reserving memory or making the container
     * immutable should be done through these functions.
     */
     
    adt_EEcode (*sort)(adt_Container *C, int reverse);
    adt_EEcode (*reserve)(adt_Container *C, va_arg sizes);
    adt_EEcode (*resize)(adt_Container *C, va_arg sizes);
    adt_EEcode (*freeze)(adt_Container *C);
    adt_EEcode (*swap)(adt_Container *C, adt_Container *O);
    adt_EEcode (*clear)(adt_Container *C);
    
    /*
     * Iterator creation, common to all containers.
     * To disable iteration, don't provide any of these functions.
     * If you do, you must provide all of them, and also implement the
     * iterator interface properly.
     * For `*keys`, the end of key values is indicated by a value with type
     * adt_VTYPE_END.
     */
    
    adt_Iterator* (*iterate)(adt_Container *C, adt_EIteratorMode mode);
    adt_Iterator* (*iterateat)(adt_Container *C, adt_EIteratorMode mode, va_arg keys);
};


struct adt_Iterator_t {
    
    /*
     * Data about the implementation
     */
    const char* (*implname)();
    size_t (*sizeofiterator)();
    
    /*
     * Iteration disposal.
     */
    
    void (*dispose)(adt_Iterator *I);
    
    /*
     * Iteration control.
     * In multi-dimensional or multi-valored keys, the iterator may return
     * a container with all the aformentioned keys. The user should NOT dispose
     * of those containers, as they're meant to be for internal use by the
     * iterator. They'll be either cleaned (perhaps to be reutilized) or
     * disposed on the next iteration.
     */
    
    adt_Value (*actual)(adt_Iterator *I);
    adt_Value (*actualkeys)(adt_Iterator *I);
    adt_Value (*next)(adt_Iterator *I);
    adt_Value (*previous)(adt_Iterator *I);
    
    /*
     * Iteration state.
     */
    
    adt_EIteratorMode (*getmode)(adt_Iterator *I);
    adt_Container* (*getcontainer)(adt_Iterator *I);
    int (*hasstarted)(adt_Iterator *I);
    int (*hasnext)(adt_Iterator *I);
    int (*hasprevious)(adt_Iterator *I);
    
    /*
     * Value control.
     * These operations take place in the actual key being iterated.
     */
    
    adt_EEcode (*set)(adt_Iterator *I, adt_Value val);
    adt_EEcode (*remove)(adt_Iterator *I);
    
    /*
     * Iterator (position-related) comparison
     */
    
    adt_EEcode (*compare)(adt_Iterator *I, adt_Iterator *O);
};


struct adt_ListApi_t {
    
    /*
     * Queries
     */
    
    int (*has)(adt_Container *C, adt_Value val);
    
    /*
     * Access
     */
    
    adt_Value (*get)(adt_Container *C, va_list keys);
    adt_Value (*set)(adt_Container *C, adt_Value val, va_list keys);
    adt_Value (*remove)(adt_Container *C, va_list keys);
    adt_Value (*insert)(adt_Container *C, adt_Value val, va_list keys);
    
    
    /*
     * Stack/queue emulation.
     * If any of those are not present, its functionality is emulated
     * with inserts and iterators.
     */
    
    adt_EEcode (*pushl)(adt_Container *C, adt_Value val);
    adt_EEcode (*pushr)(adt_Container *C, adt_Value val);
    adt_Value (*popl)(adt_Container *C);
    adt_Value (*popr)(adt_Container *C);
    
    /*
     * Shifts
     * If any of those are not present, its functionality is emulated
     * with iterators.
     */
    
    adt_EEcode (*rotl)(adt_Container *C, size_t count);
    adt_EEcode (*rotr)(adt_Container *C, size_t count);
    adt_EEcode (*crotl)(adt_Container *C, size_t count);
    adt_EEcode (*crotr)(adt_Container *C, size_t count);
};


struct adt_SetApi_t {
    
    /*
     * Access
     */
     
    adt_EEcode (*put)(adt_Container *C, adt_Value val);
    adt_Value (*remove)(adt_Container *C, adt_Value key);
    
    /*
     * Queries
     */
    
    adt_Value (*has)(adt_Container *C, adt_Value val);
};


struct adt_MapApi_t {
    
    /*
     * Access
     */
    
    adt_Value (*put)(adt_Container *C, adt_Value val, va_list keys);
    adt_Value (*remove)(adt_Container *C, va_list keys);
    
    /*
     * Queries
     */
    
    int (*has)(adt_Container *C, va_list keys);
};


struct adt_BagApi_t {
    
    size_t (*getoccurrences)(adt_Container *C, va_list keys);
    adt_Value (*removeoccurrences)(adt_Container *C, size_t amount, va_list keys);
};


struct adt_HashableApi_t {
    
    /*
     * State
     */
    adt_FHash (*gethashf)(adt_Container *C);
    
    /*
     * Actions
     */
    
    adt_EEcode (*rehash)(adt_Container *C);
};


#endif
