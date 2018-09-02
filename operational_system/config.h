#pragma once


#ifndef METROWIN
#define METROWIN
#endif
#define WINDOWS
#define WIN32


#define VARIADIC_TEMPLATE_FORMAT2


#ifdef __cplusplus
typedef wchar_t unichar;
#else
typedef unsigned short unichar;
#endif

//
//#if defined(_M_X64)  // X64
//
//
//#define AMD64
//#define OS64BIT
//#define OSBIT 64
//
//
//#elif defined(_M_IX86)
//
//
//#define X86
//#define OS32BIT
//#define OSBIT 32
//
//
//#endif

//// This avoids use of crypt for Zip compressing code
//#ifndef NOCRYPT
//#define NOCRYPT
//#endif


#ifdef _DEBUG
#define DEBUG
#endif

#ifndef _DEBUG
#define _DEBUG
#endif

#define NOMINMAX

#define DECL_C __cdecl


#define CLASS_DECL_EXPORT __declspec(dllexport)
#define CLASS_DECL_IMPORT __declspec(dllimport)
#define CLASS_DECL_THREAD __declspec(thread)

//#define NO_VARIADIC_TEMPLATE


#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif

#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_RAND_S

#define __PLACEMENT_NEW_INLINE



#define _WIDEN(x) L#x



#include "bit.h"



#define _BIND_TO_CURRENT_CRT_VERSION 1
#define _CRT_NOFORCE_MANIFEST
#define _STL_NOFORCE_MANIFEST



#pragma warning(disable:4250) // disable warning if inherited via dominance
#pragma warning(disable:4275) // disable warning about dll-interface inheriting from non-dll interface (always true for template bases)... : classical and clear linkage errors will appear if it is not template class


#define DRAWDIB_INCLUDE_STRETCHDIB

#ifdef cplus

#define inline static

#endif


#define static_inline static


#ifdef __cplusplus

#define LOG_THIS_TAG (typeid(*this).name())
#define LOG_MEMBER_PREFIX __FUNCTION__


#endif




#define FONT_SANS "Lucida Sans Unicode"
#define FONT_SERIF "Times New Roman"
#define FONT_MONO "Courier New"
#define FONT_SANS_EX "Geneva"
#define FONT_SERIF_EX "Palatino Linotype"
#define FONT_SANS_FX "Tahoma"
#define FONT_SERIF_FX "Georgia"



#define STR_NEWLINE "\r\n"