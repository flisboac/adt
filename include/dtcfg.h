
#ifndef DTCFG_H_
#define DTCFG_H_


/*##############################################################################
 * [[[   CONFIGURATION   ]]]
 */


#define dt_NAME "dt"/*@@APPNAME@@*/
#define dt_RELEASETYPE "beta"/*@@RELEASETYPE@@*/
#define dt_MAJORVERSION (0)/*@@MAJORVERSION@@*/
#define dt_MINORVERSION (1)/*@@MINORVERSION@@*/
#define dt_PATCHVERSION (0)/*@@PATCHVERSION@@*/


/*##############################################################################
 * [[[   DEFINES   ]]]
 */


#define dt_STRQT(s) #s
#define dt_STRFY(s) um_STRQT(s)

/** The release name. Do not change! */
#define dt_RELEASENAME dt_NAME \
    " " dt_STRFY(dt_MAJORVERSION) \
    "." dt_STRFY(dt_MINORVERSION) \
    "." dt_STRFY(dt_PATCHVERSION) \
    "-" dt_RELEASETYPE

#ifndef BUILDINGDOCS
#if !defined(dt_STATIC) && defined(_WIN32)
#   define dt_FIMPORT __declspec(dllimport)
#   define dt_FEXPORT __declspec(dllexport)
#   define dt_DIMPORT dt_FIMPORT
#   define dt_DEXPORT dt_FEXPORT
#else
#   define dt_FIMPORT extern
#   define dt_FEXPORT
#   define dt_DIMPORT dt_FIMPORT
#   define dt_DEXPORT
#endif


#if defined(dt_BUILDING)
#   define dt_API dt_FEXPORT
#   define dt_DATA dt_DEXPORT
#   if defined(dt_STATIC)
#       define dt_IAPI static
#       define dt_IDATA
#   else
#       if defined(__GNUC__) && ((__GNUC__*100 + __GNUC_MINOR__) >= 302) && \
                defined(__ELF__)
#           define dt_IAPI __attribute__((visibility("hidden"))) extern
#           define dt_IDATA dt_IAPI
#       else
#           define dt_IAPI extern
#           define dt_IDATA extern
#       endif
#   endif
#else
#   define dt_API dt_FIMPORT
#   define dt_DATA dt_DIMPORT
#endif
#else

#define dt_FIMPORT /**< Target-dependent marker for symbols to be exported to shared libraries. */
#define dt_FEXPORT /**< Target-dependent marker for symbols to be imported from shared libraries. */
#define dt_API     /**< Target-dependent marker for external library functions. */
#define dt_DATA    /**< Target-dependent marker for external library variables. */
#define dt_IAPI    /**< Target-dependent marker for internal library functions. */
#define dt_IDATA   /**< Target-dependent marker for internal library variables. */

#endif


#endif
