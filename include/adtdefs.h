#ifndef ADTDEFS_H_
#define ADTDEFS_H_

/* Unfortunately, the Windows environment needs special treatment.
 */
#if !defined(adt_STATIC) && defined(_WIN32)
#   define adt_FIMPORT __declspec(dllimport)
#   define adt_FEXPORT __declspec(dllexport)
#   define adt_DIMPORT adt_FIMPORT
#   define adt_FEXPORT adt_FEXPORT
/* Else, standard C qualifiers should be sufficient for the front-end API.
 */
#else
#   define adt_FIMPORT extern
#   define adt_FEXPORT
#   define adt_DIMPORT adt_FIMPORT
#   define adt_DEXPORT
#endif


#if defined(adt_BUILDING)
#   define adt_API adt_FEXPORT
#   define adt_DATA adt_DEXPORT
    /* If the build is of a static library, all file objects will be linked as
     * one huge module. In this case, internal API should be static to not be
     * exported when linking to other applications.
     */
#   if defined(adt_STATIC)
#       define adt_IAPI static
#       define adt_IDATA
    /* If the build is of a shared library, procedures are a bit different.
    */
#   else
        /* Use specific configuration for some compilers.
        */
#       if defined(__GNUC__) && ((__GNUC__*100 + __GNUC_MINOR__) >= 302) && \
                defined(__ELF__)
#           define adt_IAPI __attribute__((visibility("hidden"))) extern
#           define adt_IDATA adt_IAPI
        /* Fallback to standard C.
         */
#       else
#           define adt_IAPI extern
#           define adt_IDATA extern
#       endif
#   endif
#else
#   define adt_API adt_FIMPORT
#   define adt_DATA adt_DIMPORT
#endif


#endif
