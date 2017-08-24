#include "stdafx.h"
#include "VersionUtilTest.h"

namespace Shuanglong::Test
{
    VersionUtilTest* VersionUtilTest::mpInstance = nullptr;

    VersionUtilTest::VersionUtilTest()
    {}

    VersionUtilTest::~VersionUtilTest()
    {}

    void VersionUtilTest::Entry()
    {
        mpInstance = new VersionUtilTest();
        mpInstance->mpLog = Log::GetInstance();

        mpInstance->GetFileVersionInfoTest();
    }

    void VersionUtilTest::GetFileVersionInfoTest()
    {
        UINT vsFixedLen = 0;
        LPCSTR fileName = "E:\\sys_sdk_windows\\dlodlovr_sdk\\trunk\\wdvr_v0\\Dlodlo VR Rumtime Service\\x64\\Debug\\AutoUpdate.exe";
        DWORD infoLen = 0;
        char *pInfoBuff = nullptr;
        BOOL resBool = false;

        infoLen = GetFileVersionInfoSizeA(fileName, nullptr);
        pInfoBuff = new char[infoLen];
        resBool = GetFileVersionInfoA(fileName, NULL, infoLen, pInfoBuff);

        //VerQueryValueA(pInfoBuff, "\\", (LPVOID*)&pvsFixedFileInfo, &vsFixedLen);

        UINT cbTranslate = 0;
        HRESULT hr;
        struct LANGANDCODEPAGE
        {
            WORD wLanguage;
            WORD wCodePage;
        } *lpTranslate;

        resBool = VerQueryValueA(pInfoBuff, "\\VarFileInfo\\Translation", (LPVOID*)&lpTranslate, &cbTranslate);

        STRSAFE_LPSTR subBlock = new char[50];
        char *pOutBuffer = nullptr;
        UINT outBuffLen = 0;
        DWORD errorCode = 0;

        for (UINT i = 0; i < (cbTranslate / sizeof(struct LANGANDCODEPAGE)); i++)
        {
            hr = StringCchPrintfA(subBlock, 50, "\\StringFileInfo\\%04x%04x\\FileVersion", lpTranslate[i].wLanguage, lpTranslate[i].wCodePage);
            resBool = VerQueryValueA(pInfoBuff, subBlock, (LPVOID*)&pOutBuffer, &outBuffLen);
            if (!resBool)
            {
                errorCode = GetLastError();
            }
        }

        mpLog->Console(SL_CODELOCATION, "resBool=%s", resBool ? "true" : "false");
        mpLog->Console(SL_CODELOCATION, "fileName=%s", fileName);
    }
}
