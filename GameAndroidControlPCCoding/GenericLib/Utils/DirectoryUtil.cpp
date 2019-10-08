#include "DirectoryUtil.h"

#include <windows.h>

namespace Shuanglong::Utils
{
    std::string DirectoryUtil::GetCurrentDirectoryString()
    {
        char curDirBuffer[MAX_PATH];
        ::GetCurrentDirectoryA(MAX_PATH, curDirBuffer);
        return std::string(curDirBuffer);
    }

    std::string DirectoryUtil::GetModuleDirectoryString()
    {
        std::string moduleName = GetModuleFileNameString();
        size_t pos = moduleName.find_last_of("\\");
        return moduleName.substr(0, pos);
    }

    std::string DirectoryUtil::GetModuleFileNameString()
    {
        char curModuleFileName[MAX_PATH];
        DWORD res = ::GetModuleFileNameA(nullptr, curModuleFileName, MAX_PATH);
        return std::string(curModuleFileName);
    }

    bool DirectoryUtil::IsDirectoryExist(std::string dirPath)
    {
        bool retValue = false;

        WIN32_FILE_ATTRIBUTE_DATA fileAttributeData;
        BOOL success = ::GetFileAttributesExA(dirPath.c_str(), GetFileExInfoStandard, &fileAttributeData);
        if (success != 0 && (fileAttributeData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            retValue = true;
        }
        //else
        //{
        //    DWORD errorCode = GetLastError();// ERROR_FILE_NOT_FOUND 2(0x2)
        //}

        return retValue;
    }

    bool DirectoryUtil::IsFileExist(std::string filename)
    {
        bool retValue = false;
        WIN32_FILE_ATTRIBUTE_DATA fileAttributeData;
        BOOL success = ::GetFileAttributesExA(filename.c_str(), GetFileExInfoStandard, &fileAttributeData);
        if (success != 0 && (fileAttributeData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE))
        {
            retValue = true;
        }
        return retValue;
    }

    bool DirectoryUtil::CreateDirectoryByPath(std::string dirPath)
    {
        bool retValue = false;
        BOOL retFlag = ::CreateDirectoryA(dirPath.c_str(), NULL);
        if (retFlag)
        {
            retValue = true;
        }
        else
        {
            DWORD errorCode = ::GetLastError();
            if (errorCode == ERROR_ALREADY_EXISTS)
            {
                retValue = true;
            }
        }
        return retValue;
    }

    bool DirectoryUtil::CreateFileByName(std::string filename)
    {
        bool retValue = false;
        HANDLE hTempFile = ::CreateFileA(filename.c_str(),
                                         GENERIC_READ | GENERIC_WRITE,
                                         FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                         NULL,
                                         CREATE_NEW,
                                         FILE_ATTRIBUTE_NORMAL,
                                         NULL);
        if (hTempFile != INVALID_HANDLE_VALUE)
        {
            retValue = true;
            ::CloseHandle(hTempFile);
        }
        else
        {
            DWORD errorCode = GetLastError();
            if (errorCode == ERROR_FILE_EXISTS)
            {
                retValue = true;
            }
        }
        return retValue;
    }

    bool DirectoryUtil::RemoveDirectoryByPath(std::string dirPath)
    {
        bool retValue = false;
        return retValue;
    }

    bool DirectoryUtil::RemoveFileByName(std::string filename)
    {
        bool retValue = false;
        return retValue;
    }
}
