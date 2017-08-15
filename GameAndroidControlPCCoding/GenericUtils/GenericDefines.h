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
#define GENERIC_EXPORT __declspec(dllexport)
#else
#define GENERIC_EXPORT __declspec(dllimport)
#endif
