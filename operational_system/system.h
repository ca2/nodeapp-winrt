#pragma once


#ifdef __cplusplus

class metrowin_todo { public: metrowin_todo() {}  ~metrowin_todo() {} };

#endif

#pragma once



#ifdef __cplusplus
#pragma pointers_to_members( full_generality, virtual_inheritance )
#endif



#define NOTHROW throw()
#define THROWS throw(...)

#ifdef DEBUG
#define RELEASENOTHROW throw(...)
#else
#define RELEASENOTHROW throw()
#endif












#pragma once


#define WINDOWS
#ifndef _WINDOWS
#define _WINDOWS
#endif
#ifndef METROWIN
#define METROWIN
#endif


/////////////////////////////////////////////////////////////////////////////
// Master version numbers

#define _AFX     1      // Microsoft Application Framework Classes
#ifndef _MFC_VER
#define _MFC_VER 0x0800 // Microsoft Foundation Classes version 8.00
#endif

#define DECL_SPEC_ANY __declspec(selectany)



#ifndef DEBUG
#ifndef ___DISABLE_INLINES
//	#define ___ENABLE_INLINES
#endif
#endif

#define ___NO_NESTED_DERIVATION


/////////////////////////////////////////////////////////////////////////////
// special include files

#ifndef __INLINE
#ifdef __cplusplus
#define __INLINE inline /*__forceinline*/
#else
#define __INLINE
#endif
#endif

// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

// afxv_w32.h - target version/configuration control for Win32

#pragma once

#ifdef _WINDOWS_
#error WINDOWS.H already included.  MFC apps must not #include <windows.h>
#endif

// STRICT is the only supported option (NOSTRICT is no longer supported)
#ifndef STRICT
#define STRICT 1
#endif


#include <sdkddkver.h>

//#define  NTDDI_VERSION     0x06020000        //  NTDDI_WIN8
//#define  WINVER            0x0602            // _WIN32_WINNT_WIN8
//#define _WIN32_WINNT 	   0x0602            // _WIN32_WINNT_WIN8
//#define _WIN32_IE          0x0A00            // _WIN32_IE_IE100


#define VC_EXTRALEAN



// certain parts of WINDOWS.H are necessary
#undef NOKERNEL
#undef NOGDI
#undef NOUSER
#undef NODRIVERS
#undef NOLOGERROR
#undef NOPROFILER
#undef NOMEMMGR
#undef NOLFILEIO
#undef NOOPENFILE
#undef NORESOURCE
#undef NOATOM
#undef NOLANGUAGE
#undef NOLSTRING
#undef NODBCS
#undef NOKEYBOARDINFO
#undef NOGDICAPMASKS
#undef NOCOLOR
#undef NOGDIOBJ
#undef NODRAWTEXT
#undef NOTEXTMETRIC
#undef NOSCALABLEFONT
#undef NOBITMAP
#undef NORASTEROPS
#undef NOMETAFILE
#undef NOSYSMETRICS
#undef NOSYSTEMPARAMSINFO
#undef NOMSG
#undef NOWINSTYLES
#undef NOWINOFFSETS
#undef NOSHOWWINDOW
#undef NODEFERWINDOWPOS
#undef NOVIRTUALKEYCODES
#undef NOKEYSTATES
#undef NOWH
#undef NOMENUS
#undef NOSCROLL
#undef NOCLIPBOARD
#undef NOICONS
#undef NOMB
#undef NOSYSCOMMANDS
#undef NOMDI
#undef NOCTLMGR
#undef NOWINMESSAGES

#ifndef WIN32
#define WIN32
#endif

//#ifndef WIN32_LEAN_AND_MEAN
//#define WIN32_LEAN_AND_MEAN
//#endif

#ifdef _UNICODE
#ifndef UNICODE
#define UNICODE         // UNICODE is used by Windows headers
#endif
#endif

#ifdef UNICODE
#ifndef _UNICODE
#define _UNICODE        // _UNICODE is used by C-runtime/MFC headers
#endif
#endif

#ifdef VC_EXTRALEAN
#define NOSERVICE
#define NOMCX
#define NOIME
#define NOSOUND
#define NOCOMM
#define NORPC

#ifndef NO_ANSIUNI_ONLY
#ifdef _UNICODE
#define UNICODE_ONLY
#else
#define ANSI_ONLY
#endif
#endif //!NO_ANSIUNI_ONLY

#endif //VC_EXTRALEAN

/////////////////////////////////////////////////////////////////////////////
// Turn off warnings for /W4
// To resume any of these warning: #pragma warning(default: 4xxx)
// which should be placed after the AFX include files

#pragma warning(push)
#pragma warning(disable: 4311 4312)
#pragma warning(disable: 4201)  // winnt.h uses nameless structs
#define _WINSOCKAPI_

#include <winapifamily.h>
#include <windows.h>
#include <shlwapi.h>
#include <shellapi.h>
#include <winuser.h>
#if defined(__cplusplus_winrt)
#include <wrl/client.h>
#define __PLACEMENT_NEW_INLINE
#define _IOSFWD_
#define _ALGORITHM_
#define std _std
#include <agile.h>
#undef std
#endif
#if defined(__cplusplus_winrt)
using namespace Platform;
using namespace Windows::System;
using namespace Windows::System::Threading;
using namespace Windows::Storage;
#endif


#include "_stdint.h"

#include "oswindow.h"



#if defined(__cplusplus_winrt)

namespace dx
{
   //inline void throw_if_failed(HRESULT hr)
   //{
   //   if(FAILED(hr))
   //   {
   //      // Set a breakpoint on this line to catch DirectX API errors
   //      throw Platform::Exception::CreateException(hr);
   //   }
   //}

   struct ByteArray { Platform::Array<byte>^ data; };

   // function that reads from a binary file asynchronously
   /*	inline Concurrency::task<ByteArray> ReadDataAsync(Platform::String^ filename)
   {
   using namespace Windows::Storage;
   using namespace Concurrency;

   auto folder = Windows::ApplicationModel::Package::Current->InstalledLocation;

   task<StorageFile^> getFileTask(folder->GetFileAsync(filename));

   auto readBufferTask = getFileTask.then([] (StorageFile^ f)
   {
   return FileIO::ReadBufferAsync(f);
   });

   auto byteArrayTask = readBufferTask.then([] (Streams::IBuffer^ b) -> ByteArray
   {
   auto a = ref new Platform::Array<byte>(b->Length);
   Streams::DataReader::FromBuffer(b)->ReadBytes(a);
   ByteArray ba = { a };
   return ba;
   });

   return byteArrayTask;
   }*/
} // namespace dx

#endif // #if defined(__cplusplus_winrt)


#pragma warning(pop)

// Mouse message MFC is interested in
#ifndef __WM_MOUSELAST
#define __WM_MOUSELAST 0x0209
#endif

//#include <zmouse.h>

#include <Combaseapi.h>

struct HKEY__;
typedef struct HKEY__ *HKEY;

#ifndef _INC_COMMCTRL
#include <commctrl.h>

// Note: We must avoid using TB_ADDBUTTONW and TB_INSERTBUTTONW
//       in the Unicode build or else MFC80U.DLL will not be
//       compatible with pre-IE4 versions of COMCTL32.DLL.
#ifdef TB_ADDBUTTONSA
#undef TB_ADDBUTTONS
#define TB_ADDBUTTONS TB_ADDBUTTONSA
#endif

#ifdef TB_INSERTBUTTONA
#undef TB_INSERTBUTTON
#define TB_INSERTBUTTON TB_INSERTBUTTONA
#endif
#endif

#ifndef EXPORT
#define EXPORT
#endif

#ifndef _INC_TCHAR
#include <tchar.h>      // used for ANSI v.s. UNICODE abstraction
#endif
#ifdef _MBCS
#ifndef _INC_MBCTYPE
#include <mbctype.h>
#endif
#ifndef _INC_MBSTRING
#include <mbstring.h>
#endif
#endif

#ifdef _WIN64
#define ___NO_CTL3D_SUPPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// Now for the Windows API specific parts

// WM_CTLCOLOR for 16 bit API compatability
#define WM_CTLCOLOR     0x0019

// Win32 uses macros with parameters for this, which breaks C++ code.
#ifdef __cplusplus
#ifdef GetWindowTask
#undef GetWindowTask
#ifdef _WIN32
__INLINE HTASK GetWindowTask(HWND hWnd)
{
   return (HTASK)(DWORD_PTR)GetWindowThreadProcessId(hWnd,NULL);
}
#endif
#endif

// Win32 uses macros with parameters for this, which breaks C++ code.
#ifdef GetNextWindow
#undef GetNextWindow
__INLINE HWND GetNextWindow(HWND hWnd,UINT nDirection)
{
   return GetWindow(hWnd,nDirection);
}
#endif
#endif

#include <ws2tcpip.h>
//#include <tpipv6.h>  // For IPv6 Tech Preview.



#define WIN32_LEAN_AND_MEAN
//#include <ws2tcpip.h>
#if _MSC_VER < 1200
#ifndef __CYGWIN__
#ifdef ENABLE_IPV6
#include <tpipv6.h>  // For IPv6 Tech Preview.
#endif
#endif
#endif // _MSC_VER < 1200



// Include any non-Intel platform specific items
#ifndef X86
#include "version_cpu.h"
#endif

#ifdef X86
#define ___MINREBUILD
#endif

#ifdef _CUSTOM
// Put any custom configuration items in afxv_cfg.h
#include <afxv_cfg.h>
#endif

// setup default packing value
#ifndef ___PACKING
#define ___PACKING    4   // default packs structs at 4 bytes
#endif

#include "version_dll.h"

// Define this virtual key for use by status bar
#ifndef VK_KANA
#define VK_KANA             0x15
#endif

/////////////////////////////////////////////////////////////////////////////
// Special __debug_break: used to break into debugger at critical times

#define debug_break() __debugbreak()

/*#ifndef DEBUG
#ifdef __debug_break
#undef __debug_break
#endif
#define __debug_break()
#endif  // DEBUG*/

/////////////////////////////////////////////////////////////////////////////
// Standard preprocessor symbols if not already defined
/////////////////////////////////////////////////////////////////////////////

// SIZE_T_MAX is used by the collection classes
#ifndef SIZE_T_MAX
#define SIZE_T_MAX  UINT_MAX
#endif

// is used for static member functions
#ifndef PASCAL
#define  __stdcall
#endif

// FASTCALL is used for static member functions with little or no params
#ifndef FASTCALL
#define FASTCALL __fastcall
#endif

// CDECL and EXPORT are defined in case WINDOWS.H doesn't
#ifndef CDECL
#define CDECL __cdecl
#endif

#ifndef EXPORT
#define EXPORT
#endif

// UNALIGNED is used for unaligned data access (in CArchive mostly)
#if !defined(UNALIGNED)
#if defined(_M_IA64) || defined(_M_AMD64)
#define UNALIGNED __unaligned
#else
#define UNALIGNED
#endif
#endif

// __DEPRECATED is used for functions that should no longer be used
#ifndef __DEPRECATED
#ifdef ___DISABLE_DEPRECATED
#define __DEPRECATED(_Message)
#else
#define __DEPRECATED(_Message) __declspec(deprecated(_Message))
#endif
#endif

// ___INSECURE_DEPRECATE is used for deprecated, insecure functions.
#ifndef ___INSECURE_DEPRECATE
#ifdef ___SECURE_NO_DEPRECATE
#define ___INSECURE_DEPRECATE(_Message)
#else
#define ___INSECURE_DEPRECATE(_Message) __declspec(deprecated(_Message))
#endif // ___SECURE_NO_DEPRECATE
#endif // ___INSECURE_DEPRECATE

// AFXAPI is used on global public functions
#ifndef AFXAPI
#define AFXAPI __stdcall
#endif

// AFXOLEAPI is used for some special OLE functions
#ifndef AFXOLEAPI
#define AFXOLEAPI __stdcall
#endif

// c_cdecl is used for rare functions taking variable arguments
#ifndef c_cdecl
#define c_cdecl __cdecl
#endif

// __EXPORT is used for functions which need to be exported
#ifndef __EXPORT
#define __EXPORT EXPORT
#endif

#ifndef __STATIC
#define __STATIC extern
#define __STATIC_DATA extern __declspec(selectany)
#endif

// The following macros are used to enable export/import

// for data
#ifndef __DATA_EXPORT
#define __DATA_EXPORT __declspec(dllexport)
#endif
#ifndef __DATA_IMPORT
#define __DATA_IMPORT __declspec(dllimport)
#endif

// for classes
#ifndef __CLASS_EXPORT
#define __CLASS_EXPORT __declspec(dllexport)
#endif
#ifndef __CLASS_IMPORT
#define __CLASS_IMPORT __declspec(dllimport)
#endif

// for global APIs
#ifndef __API_EXPORT
#define __API_EXPORT __declspec(dllexport)
#endif
#ifndef __API_IMPORT
#define __API_IMPORT __declspec(dllimport)
#endif

// This macro is used to reduce size requirements of some classes
#ifndef __ALWAYS_VTABLE
#ifndef __NOVTABLE
#if _MSC_VER >= 1100 && !defined(DEBUG)
#define __NOVTABLE __declspec(novtable)
#else
#define __NOVTABLE
#endif
#endif
#endif

// for global data that should be in COMDATs (packaged data)
#ifndef __COMDAT
#define __COMDAT __declspec(selectany)
#endif

// The following macros are used on data declarations/definitions
//  (they are redefined for extension DLLs and the shared MFC DLL)
#define __DATADEF
#define __API CLASS_DECL_AURA

// used when building the "core" MFC80.DLL
#ifndef __CORE_DATA
#define __CORE_DATA CLASS_DECL_AURA
#define __CORE_DATADEF
#endif

// used when building the MFC/OLE support MFCO80.DLL
#ifndef __OLE_DATA
#define __OLE_DATA
#define __OLE_DATADEF
#endif

// used when building the MFC/DB support MFCD80.DLL
#ifndef __DB_DATA
#define __DB_DATA
#define __DB_DATADEF
#endif

// used when building the MFC/NET support MFCN80.DLL
#ifndef __NET_DATA
#define __NET_DATA
#define __NET_DATADEF
#endif

// used when building extension DLLs
#ifndef __EXT_DATA
#define __EXT_DATA
#define __EXT_DATADEF
#define __EXT_CLASS
#define __EXT_API
#endif

// BASED_XXXX macros are provided for backward compatibility
#ifndef BASED_CODE
#define BASED_CODE
#endif

#ifndef BASED_DEBUG
#define BASED_DEBUG
#endif

#ifndef BASED_STACK
#define BASED_STACK
#endif





#include "version_cpu.h"






// ca2 API inline constructors (including compiler generated) can get deep
#pragma inline_depth(16)

#ifdef ___DEVBUILD
#define __IMPL_DATA __DATA_EXPORT
#else
#define __IMPL_DATA CLASS_DECL_AURA
#endif


// #define ___NOFORCE_LIBS
#define ___FULLTYPEINFO
#define VC_EXTRALEAN
#define NO_ANSIUNI_ONLY
#define _MFC_OVERRIDES_NEW

#define __COMDAT __declspec(selectany)

#define MAX_DWORD_PTR ((dword_ptr)(-1))



#define DECLSPEC_NO_RETURN __declspec(noreturn)


//typedef INT_PTR         int_ptr,* pint_ptr;
//typedef UINT_PTR        uint_ptr,* puint_ptr;
//typedef LONG_PTR        long_ptr,* plong_ptr;
//typedef ULONG_PTR       ulong_ptr,* pulong_ptr;
//typedef DWORD_PTR       dword_ptr,* pdword_ptr;



#include "cross/cross.h"





#include <stdio.h>
#include <mmsystem.h>




//CLASS_DECL_AURA Platform::String ^ rtstr(const char * psz);
//CLASS_DECL_AURA Platform::String ^ itoa_dup(int i);
CLASS_DECL_AURA int MessageBox(oswindow window,const char * pszMessage,const char * pszTitle,int iFlags);



/*template < class T > Windows::Foundation::IAsyncOperation < T > ^ m_wait(Windows::Foundation::IAsyncOperation < T> ^ op)
{
simple_event ev;
Windows::Foundation::IAsyncOperation < T > op;
op->Completed = [](Windows::Foundation::IAsyncOperation<TResult> asyncInfo, Windows::Foundation::AsyncStatus asyncStatus)
{
if(asyncStatus == Windows::Foundation::AsyncStatusOk)
{
op = asyncInfo;
}
ev.set_event();
};
ev.wait();
return op;
}
*/








#define MOVE_SEMANTICS

//#define IMPLEMENT_VISTA_TOOLS
#define WIN32
#define DRAWDIB_INCLUDE_STRETCHDIB
#ifdef __cplusplus
#pragma pointers_to_members( full_generality, virtual_inheritance )
#endif


#define _BIND_TO_CURRENT_CRT_VERSION 1
#define _CRT_NOFORCE_MANIFEST
#define _STL_NOFORCE_MANIFEST


BEGIN_EXTERN_C


__declspec(selectany)  int _forceCRTManifest;


END_EXTERN_C


#define NOTHROW throw()
#define THROWS throw(...)


#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif


//#include "inttypes.h"
//#include "integer_type.h"




//typedef int_ptr ssize_t;
//typedef void * HDROP;
//DECLARE_HANDLE(HDROP);

typedef wchar_t unichar;
typedef unsigned int unichar32;

#define WINBOOL BOOL
#define WINUCHAR UCHAR
#define WINULONG ULONG
#define PWINUCHAR PUCHAR
#define PWINULONG PULONG
#define WINUSHORT USHORT



