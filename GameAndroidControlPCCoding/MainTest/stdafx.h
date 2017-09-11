// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// glog defines
#define GOOGLE_GLOG_DLL_DECL
#define GLOG_NO_ABBREVIATED_SEVERITIES

// Windows Header Files:
#include <windows.h>
#include <strsafe.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <VersionHelpers.h>
#include <Shlobj.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include <iostream>
#include <string>

#include <mutex>
#include <atomic>
