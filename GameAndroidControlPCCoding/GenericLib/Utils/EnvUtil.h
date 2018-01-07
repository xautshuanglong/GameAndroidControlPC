#pragma once
#include "../GenericDefines.h"

namespace Shuanglong::Utils
{
    class GENERIC_EXPORT EnvUtil sealed
    {
    private:
        EnvUtil();

    public:
        ~EnvUtil();

        static bool IsBigEndian();
        static bool IsLittleEndian();
    };
}
