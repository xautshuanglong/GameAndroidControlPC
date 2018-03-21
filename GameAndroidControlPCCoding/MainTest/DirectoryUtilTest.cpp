#include "stdafx.h"
#include "DirectoryUtilTest.h"

#include <AclAPI.h>

#include <Utils/StringUtil.h>

namespace Shuanglong::Test
{
    DirectoryUtilTest* DirectoryUtilTest::mpInstance = nullptr;

    DirectoryUtilTest::DirectoryUtilTest()
    {
        ;
    }

    DirectoryUtilTest::~DirectoryUtilTest()
    {
        ;
    }

    void DirectoryUtilTest::Entry()
    {
        mpInstance = new DirectoryUtilTest();
        mpInstance->mpLog = Log::GetInstance();

        std::cout << std::endl << "----------------------------------- Directory Utils Testing -----------------------------------" << std::endl;
        mpInstance->DirectoryUtilTest_Try();
        //mpInstance->DirectoryUtilTest_GetEnv();
    }

    void DirectoryUtilTest::DirectoryUtilTest_Try()
    {
        char curDirBuffer[512];
        GetCurrentDirectoryA(512, curDirBuffer);
        mpLog->Console("Current Directory: %s", curDirBuffer);

        char curModuleFileName[MAX_PATH];
        DWORD res = GetModuleFileNameA(nullptr, curModuleFileName, MAX_PATH);
        mpLog->Console(SL_CODE_LOCATION, "curModuleFileName=%s", curModuleFileName);

        char *pOutFileName = new char[MAX_PATH];
        _get_pgmptr(&pOutFileName);
        mpLog->Console(SL_CODE_LOCATION, "pOutFileName = %s", pOutFileName);

        char fullPathBuffer[512];
        char *pFilePart = nullptr;
        GetFullPathNameA("Log.h", 512, fullPathBuffer, &pFilePart);
        mpLog->Console("Full Path: %s", fullPathBuffer);
        mpLog->Console("File Name : %s", pFilePart);

        DWORD fileAttributes = GetFileAttributesA("Log.h");
        mpLog->Console("File Attribut : %d", fileAttributes);

        WIN32_FILE_ATTRIBUTE_DATA fileAttributeData;
        BOOL success = GetFileAttributesExA("Log.h", GetFileExInfoStandard, &fileAttributeData);
        if (success == 0)
        {
            mpLog->Console(SL_CODE_LOCATION, "Get file attributes faild %d", GetLastError());
        }
        else
        {
            mpLog->Console("FileAttributes=%d      FileSizeHigh=%d      FileSizeLow=%d",
                           fileAttributeData.dwFileAttributes, fileAttributeData.nFileSizeHigh, fileAttributeData.nFileSizeLow);

            unsigned long long ulongTime = fileAttributeData.ftCreationTime.dwHighDateTime;
            ulongTime = ulongTime << 32 | fileAttributeData.ftCreationTime.dwLowDateTime;
            mpLog->Console("CreationTime: 0x%X  0x%X    ulong: %llu",
                           fileAttributeData.ftCreationTime.dwHighDateTime, fileAttributeData.ftCreationTime.dwLowDateTime, ulongTime);

            SYSTEMTIME sysTime;
            FILETIME localFileTime;
            FileTimeToLocalFileTime(&fileAttributeData.ftCreationTime, &localFileTime);
            FileTimeToSystemTime(&localFileTime, &sysTime);
            mpLog->Console("SystemTime: %d-%02d-%02d %02d:%02d:%02d",
                           sysTime.wYear, sysTime.wMonth, sysTime.wDay,
                           sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

            FileTimeToLocalFileTime(&fileAttributeData.ftLastWriteTime, &localFileTime);
            FileTimeToSystemTime(&localFileTime, &sysTime);
            mpLog->Console("SystemTime: %d-%02d-%02d %02d:%02d:%02d",
                           sysTime.wYear, sysTime.wMonth, sysTime.wDay,
                           sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

            FileTimeToLocalFileTime(&fileAttributeData.ftLastAccessTime, &localFileTime);
            FileTimeToSystemTime(&localFileTime, &sysTime);
            mpLog->Console("SystemTime: %d-%02d-%02d %02d:%02d:%02d",
                           sysTime.wYear, sysTime.wMonth, sysTime.wDay,
                           sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

            ULARGE_INTEGER largeTime;
            largeTime.HighPart = fileAttributeData.ftCreationTime.dwHighDateTime;
            largeTime.LowPart = fileAttributeData.ftCreationTime.dwLowDateTime;
            mpLog->Console("LargeTime: %I64u", largeTime.QuadPart);
            mpLog->Console("LargeTime: %llu", largeTime.QuadPart);
        }

        BOOL existFlag = PathFileExists(L"E:\\TempLog.txt");// Shlwapi.h Shlwapi.lib
        mpLog->Console(SL_CODE_LOCATION, "existFlag=%s", existFlag ? "true" : "false");

        // 测试文件夹权限
        PACL pOldDACL = NULL, pNewDACL = NULL;
        PSID pOwnerSID = NULL, pGroupSID = NULL;
        PSECURITY_DESCRIPTOR pSD = NULL;
        DWORD dwRes = ::GetNamedSecurityInfoA(".\\", SE_FILE_OBJECT,
                                     DACL_SECURITY_INFORMATION | OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION,
                                     &pOwnerSID, &pGroupSID, &pOldDACL, NULL, &pSD);
        if (ERROR_SUCCESS != dwRes)
        {
            printf("GetNamedSecurityInfo Error %u\n", dwRes);
        }
        else
        {
            SECURITY_DESCRIPTOR secDes = *(PISECURITY_DESCRIPTOR)(pSD);
            BOOL daclPresent = FALSE;
            BOOL daclDefaulted = FALSE;
            PACL pOutAcl;
            BOOL testFlag = ::GetSecurityDescriptorDacl(pSD, &daclPresent, &pOutAcl, &daclDefaulted);

            //ACL_SIZE_INFORMATION aclSizeInfo;
            //::GetAclInformation(pOldDACL, &aclSizeInfo, sizeof(ACL_SIZE_INFORMATION), AclSizeInformation);

            LPVOID pAce = nullptr;
            for (int i = 0; i < pOldDACL->AceCount; ++i)
            {
                BOOL testFlag1 = ::GetAce(pOldDACL, i, &pAce);
                PACCESS_ALLOWED_ACE pTempAce = (PACCESS_ALLOWED_ACE)pAce;
                printf("AceType:0x%02x AceFlags:0x%02x\n",
                       pTempAce->Header.AceType,
                       pTempAce->Header.AceFlags); // CONTAINER_INHERIT_ACE
                int pause = 0;
            }

            //LogonUserA()

            PSID pOwnerSID1 = NULL;
            BOOL ownerDefaulted = FALSE;
            BOOL testFlag2 = ::GetSecurityDescriptorOwner(pSD, &pOwnerSID1, &ownerDefaulted);
            
            PTOKEN_GROUPS pTokenGroup = NULL;
            PTOKEN_OWNER pTokenOwner = NULL;
            DWORD dwLength = 0;
            HANDLE tokenHandle = NULL;
            HANDLE tokenHandleDup = NULL;
            HANDLE hCurProcess = ::GetCurrentProcess();
            BOOL bSuccess = ::OpenProcessToken(hCurProcess, TOKEN_ALL_ACCESS, &tokenHandle);
            if (bSuccess)
            {
                bSuccess = ::DuplicateTokenEx(tokenHandle, TOKEN_ALL_ACCESS, NULL, SecurityIdentification, TokenPrimary, &tokenHandleDup);
                //BOOL test1 = GetTokenInformation(tokenHandleDup, TokenGroups, (LPVOID)pTokenGroup, 0, &dwLength);
                //DWORD errorCode = 0;
                //if (!test1)
                //{
                //    errorCode = GetLastError();
                //}
                //pTokenGroup = (PTOKEN_GROUPS)new BYTE[dwLength];
                //memset(pTokenGroup, 0, dwLength);
                //BOOL test2 = GetTokenInformation(tokenHandleDup, TokenGroups, (LPVOID)pTokenGroup, dwLength, &dwLength);
                //if (!test2)
                //{
                //    errorCode = GetLastError();
                //}
                BOOL test1 = GetTokenInformation(tokenHandleDup, TokenOwner, (LPVOID)pTokenOwner, 0, &dwLength);
                DWORD errorCode = 0;
                if (!test1)
                {
                    errorCode = GetLastError();
                }
                pTokenOwner = (PTOKEN_OWNER)new BYTE[dwLength];
                memset(pTokenOwner, 0, dwLength);
                BOOL test2 = GetTokenInformation(tokenHandleDup, TokenOwner, (LPVOID)pTokenOwner, dwLength, &dwLength);
                if (!test2)
                {
                    errorCode = GetLastError();
                }
                int i = 0;
            }

            //SetEntriesInAcl
            int aclSize = sizeof(ACL);
            int aceSize = sizeof(ACCESS_ALLOWED_OBJECT_ACE);
            int i = 0;
        }

        if (pSD != NULL)
            LocalFree((HLOCAL)pSD);
        if (pNewDACL != NULL)
            LocalFree((HLOCAL)pNewDACL);


        // 创建文件夹
        bool retValue = false;
        BOOL retFlag = ::CreateDirectoryA(".\\TestDir", NULL);
        if (retFlag)
        {
            mpLog->Console(SL_CODE_LOCATION, "Create dir successfully!");
        }
        else
        {
            DWORD errorCode = ::GetLastError();
            if (errorCode == ERROR_ALREADY_EXISTS)
            {
                mpLog->Console(SL_CODE_LOCATION, "errorCode == ERROR_ALREADY_EXISTS");
            }
            else
            {
                mpLog->Console(SL_CODE_LOCATION, "errorCode == %lu", errorCode);
            }
        }
    }

    void DirectoryUtilTest::DirectoryUtilTest_GetEnv()
    {
        size_t     returnValue = 0;
        errno_t    errorCode = 0;
        BOOL       retBool = FALSE;
        char       buffer[MAX_PATH];

        errorCode = getenv_s(&returnValue, buffer, MAX_PATH, "HomePath");
        mpLog->Console(SL_CODE_LOCATION, "HomePath=%s ErrorCode=%d", buffer, errorCode);

        errorCode = getenv_s(&returnValue, buffer, MAX_PATH, "UserProfile");
        mpLog->Console(SL_CODE_LOCATION, "UserProfile=%s ErrorCode=%d", buffer, errorCode);

        errorCode = _putenv_s("PUTENV_TEST", "PUTENV_TEST FROM GameAndroidControlPC");
        mpLog->Console(SL_CODE_LOCATION, "After _putenv_s PUTENV_TEST ErrorCode=%d", errorCode);

        errorCode = getenv_s(&returnValue, buffer, MAX_PATH, "PUTENV_TEST");
        mpLog->Console(SL_CODE_LOCATION, "PUTENV_TEST=%s  ErrorCode=%d", buffer, errorCode);

        LPITEMIDLIST pidl;
        LPMALLOC     pShellMalloc;
        TCHAR szDir[MAX_PATH] = { 0 };
        SHGetMalloc(&pShellMalloc);
        SHGetSpecialFolderLocation(NULL, CSIDL_LOCAL_APPDATA, &pidl);
        SHGetPathFromIDList(pidl, szDir);
        pShellMalloc->Free(pidl);

        retBool = SHGetSpecialFolderPathA(nullptr, buffer, CSIDL_LOCAL_APPDATA, false);
        mpLog->Console(SL_CODE_LOCATION, "CSIDL_LOCAL_APPDATA=%s  ReturnBool=%s", buffer, retBool ? "true" : "false");

        retBool = SHGetSpecialFolderPathA(nullptr, buffer, CSIDL_PROFILE, false);
        mpLog->Console(SL_CODE_LOCATION, "CSIDL_PROFILE=%s  ReturnBool=%s", buffer, retBool ? "true" : "false");

        WCHAR *wpBuffer = new WCHAR[MAX_PATH];
        SHGetKnownFolderPath(FOLDERID_Downloads, 0, nullptr, &wpBuffer);
        mpLog->Console(SL_CODE_LOCATION, "FOLDERID_Downloads=%s", Utils::StringUtil::WStringToString(wpBuffer).c_str());

        CoTaskMemFree(wpBuffer);
    }
}
