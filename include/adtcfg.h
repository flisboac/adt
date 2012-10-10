/**
 * @file include/adtcfg.h
 */

#ifndef ADTCFG_H_
#define ADTCFG_H_


/*
 * [ C O N S T A N T S ] =======================================================
 */


#define adt_STRQT(s) #s
#define adt_STRFY(s) um_STRQT(s)


/*
 * [ C O N F I G U R A T I O N ] ===============================================
 */


#define adt_NAME "adt"/*@@APPNAME@@*/
#define adt_RELEASETYPE "beta"/*@@RELEASETYPE@@*/
#define adt_MAJORVERSION (0)/*@@MAJORVERSION@@*/
#define adt_MINORVERSION (1)/*@@MINORVERSION@@*/
#define adt_PATCHVERSION (0)/*@@PATCHVERSION@@*/

/* Do not change! */
#define adt_RELEASENAME adt_NAME \
	" " adt_STRFY(adt_MAJORVERSION) \
	"." adt_STRFY(adt_MINORVERSION) \
	"." adt_STRFY(adt_PATCHVERSION) \
	"-" adt_RELEASETYPE


/*
 * [ M A R K E R S ] ===========================================================
 */


#if !defined(adt_STATIC) && defined(_WIN32)
#   define adt_FIMPORT __declspec(dllimport)
#   define adt_FEXPORT __declspec(dllexport)
#   define adt_DIMPORT adt_FIMPORT
#   define adt_DEXPORT adt_FEXPORT
#else
#   define adt_FIMPORT extern
#   define adt_FEXPORT
#   define adt_DIMPORT adt_FIMPORT
#   define adt_DEXPORT
#endif


#if defined(adt_BUILDING)
#   define adt_API adt_FEXPORT
#   define adt_DATA adt_DEXPORT
#   if defined(adt_STATIC)
#       define adt_IAPI static
#       define adt_IDATA
#   else
#       if defined(__GNUC__) && ((__GNUC__*100 + __GNUC_MINOR__) >= 302) && \
                defined(__ELF__)
#           define adt_IAPI __attribute__((visibility("hidden"))) extern
#           define adt_IDATA adt_IAPI
#       else
#           define adt_IAPI extern
#           define adt_IDATA extern
#       endif
#   endif
#else
#   define adt_API adt_FIMPORT
#   define adt_DATA adt_DIMPORT
#endif


#endif /* ADTCFG_H_ */
