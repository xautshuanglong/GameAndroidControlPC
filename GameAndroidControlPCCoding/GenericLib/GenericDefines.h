#pragma once
/**************************************************************************\
 *  FileName: CommonDefines.h
 *
 *  Author  : JiangShuanglong
 *  Date    : 2017-01-01 14:43:23
 *
 *  Description: Some general definitions
\**************************************************************************/

#if _UNICODE
#else
#endif

#ifdef _USRDLL
#  ifdef GENERICUTILS_EXPORTS
#      define GENERIC_EXPORT __declspec(dllexport)
#  else
#      define GENERIC_EXPORT __declspec(dllimport)
#  endif
#else
#  define GENERIC_EXPORT
#endif // _USRDLL

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#  ifndef OS_WINDOWS
#  define OS_WINDOWS
#  endif
#elif defined(__CYGWIN__) || defined(__CYGWIN32__)
#  ifndef OS_CYGWIN
#  define OS_CYGWIN
#  endif
#elif defined(linux) || defined(__linux) || defined(__linux__)
#  ifndef OS_LINUX
#  define OS_LINUX
#  endif
#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
#  ifndef OS_MACOSX
#  define OS_MACOSX
#  endif
#elif defined(__FreeBSD__)
#  ifndef OS_FREEBSD
#  define OS_FREEBSD
#  endif
#elif defined(__NetBSD__)
#  ifndef OS_NETBSD
#  define OS_NETBSD
#  endif
#elif defined(__OpenBSD__)
#  ifndef OS_OPENBSD
#  define OS_OPENBSD
#  endif
#else
// TODO: Add other platforms.
#endif

#define DECLARE_SHARED_POINTER(clsName) typedef std::shared_ptr<clsName> Ptr##clsName;

namespace Shuanglong
{
    namespace Utils
    {
    }
}

namespace Shuanglong
{
    namespace Algorithm
    {
    }
}
