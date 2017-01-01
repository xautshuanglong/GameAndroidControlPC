#pragma once

/**************************************************************************\
 *  FileName: CommonDefines.h
 *
 *  Author  : JiangShuanglong
 *  Date    : 2017-01-01 18:29:03
 *
 *  Description: Some general defines
\**************************************************************************/

#if GENERICUTILS_EXPORTS
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API __declspec(dllimport)
#endif
