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
#  define OS_WINDOWS
#elif defined(__CYGWIN__) || defined(__CYGWIN32__)
#  define OS_CYGWIN
#elif defined(linux) || defined(__linux) || defined(__linux__)
#  ifndef OS_LINUX
#  define OS_LINUX
#  endif
#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
#  define OS_MACOSX
#elif defined(__FreeBSD__)
#  define OS_FREEBSD
#elif defined(__NetBSD__)
#  define OS_NETBSD
#elif defined(__OpenBSD__)
#  define OS_OPENBSD
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
