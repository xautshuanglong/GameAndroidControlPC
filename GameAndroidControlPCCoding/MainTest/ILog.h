#pragma once
#include "CodeLocation.h"

using namespace Shuanglong::Utils;

namespace Shuanglong
{
    class ILog
    {
    public:
        virtual void Console(const char* msgFormat, ...) = 0;
        virtual void Console(CodeLocation location, char* msgFormat, ...) = 0;

        virtual void WriteFile(const char* msgFormat, ...) = 0;
        virtual void WriteFile(CodeLocation location, char* msgFormat, ...) = 0;
    };
}
