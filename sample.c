
/*
All types starts with 'dt', followed by its name (e.g. 'Vector'), and a suffix
that hints what the name refers to. Any suffix starting with an underline '_'
is a definition, else, it's a declaration. Suffixes are generally a single 
upper case letter (or two, when in use for iterators).

All types with a suffix, as described above, are macros in C. All of the macros
receive a type as its argument.

Possible letters:
N - Container's base data typename
T - Container's complete data typename
D - Container's base data structure, only data.
S - Container's complete data structure, with data and helper fields.
A - Container's API typename (roughly, the container's class)
C - Recovers the container's API
U - An utility structure used on macro's algorithms.
M - Starter for an aliased container's function (a 'method'). You need to
    declare the container's functions for them to work.
F - Starter for a container's macro function. Macro functions works on
    Base data structures, not on complete ones.

All letter sequences starting with 'I' are markers for iterators. All the
above markers apply for iterators (e.g. IN, IT, ID, etc).

There's also two basic "post-suffixes" used on any of the above types:
_decl - Emits a declaration. It's generally used in header files or
        inside functions.
_defn - Emits a definition. It's generally used on source files. MUST be put
        outside functions, as it emits code.
_decm - Same as _decl, but emit markers, according to the build type used.
_defm - Same as _defn, but emit markers, according to the build type used.

There's also the following raw types' typedefs (observing availability)
- dtptrdiff: ptrdiff_t
- dtoffset: offset_t
- dtsize: size_t
- dtwchar: wchar_t
- dtchar: char
- dtuchar: unsigned char
- dtshort: short
- dtushort: unsigned short
- dtint: int
- dtuint: unsigned int
- dtlong: long
- dtulong: unsigned long
- dtllong: long long
- dtullong: unsigned long long
- dtfloat: float
- dtdouble: double
- dtldouble: long double
- dtcharp: char*
- dtwcharp: wchar_t*
- dtsizep: size_t*
- dtvoidp: void*

Basically, for this library to work, any C type comprised of more than one
token or of punctuation needs to be typedef'd (aliased) to a single token, to
circumvent the pre-processor limitations.

*/


#define dtVectorN(RT) dtVector__ ## RT ## __data
#define dtVectorT(RT) dtVector__ ## RT ## __ctnr
#define dtVectorA(RT) dtVector__ ## RT ## __api

#define dtVectorU(RT) \
struct { \
    RT ret; \
}

#define dtVectorD(RT) \
struct dtVectorN(RT) ## _ { \
    size_t cap; \
    size_t len; \
    union { \
        RT *ptr; \
        void *vptr; \
    } \
}

#define dtVectorS(RT) \
struct dtVectorT(RT) ## _ { \
    dtCtnr base; \
    dtVectorD(RT) data; \
}

#define dtVectorC(RT, c) ((dtVectorA(RT)) ((c) ? ((c)->base).api : NULL))

dtVectorF_push(RT, c, aux, {/*success*/}, {/*failure*/})

dtVectorM_push(RT, c, value) | dtVectorA(RT)->
dtVectorM_pop(RT, c)

