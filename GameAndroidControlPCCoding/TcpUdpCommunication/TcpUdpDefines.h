#pragma once

/**************************************************************************\
 *  FileName: CommonDefines.h
 *
 *  Author  : JiangShuanglong
 *  Date    : 2017-01-01 18:29:03
 *
 *  Description: Some general defines
\**************************************************************************/

#if TCPUDPCOMMUNICATION_EXPORTS
#define TCPUDP_EXPORT __declspec(dllexport)
#else
#define TCPUDP_EXPORT __declspec(dllimport)
#endif
