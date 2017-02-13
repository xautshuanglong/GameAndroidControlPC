#pragma once
#include "CommonDefines.h"
#include "ILog.h"

EXPORT_API void GenericUtilsTestEntry(ShuangLong::ILog *pLog);

void TimeUtilTest();
void DirectoryUtilTest();

void StringUtilTest();
void StringUtilTest_Trim();
void StringUtilTest_TrimW();
void StringUtilTest_Split();
void StringUtilTest_SplitW();
void StringUtilTest_StringToWStringAPI();
void StringUtilTest_WStringToStringAPI();
void StringUtilTest_WStringToString();
void StringUtilTest_StringToWString();