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

#if GENERICUTILS_EXPORTS
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API //__declspec(dllimport)// need not __declspec(dllimport) as static library
#endif

