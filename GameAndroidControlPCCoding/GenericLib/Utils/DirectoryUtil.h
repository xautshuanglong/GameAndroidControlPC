#pragma once
#include "../GenericDefines.h"

#include <string>

namespace Shuanglong::Utils
{
    class GENERIC_EXPORT DirectoryUtil sealed
    {
    public:
        DirectoryUtil() = delete;
        DirectoryUtil(const DirectoryUtil& originalObj) = delete;
        DirectoryUtil(DirectoryUtil&& originalObj) = delete;

        static std::string GetCurrentDirectoryString();
        static std::string GetModuleDirectoryString();
        static std::string GetModuleFileNameString();
        
        static bool IsDirectoryExist(std::string dirPath);
        static bool IsFileExist(std::string filename);

        static bool CreateDirectoryByPath(std::string dirPath);
        static bool CreateFileByName(std::string filename);

        static bool RemoveDirectoryByPath(std::string dirPath);
        static bool RemoveFileByName(std::string filename);
    };
}
