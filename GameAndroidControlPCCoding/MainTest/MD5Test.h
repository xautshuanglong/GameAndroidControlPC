#pragma once

namespace Shuanglong::Test
{
    class MD5Test
    {
    private:
        MD5Test();
        static MD5Test* GetInstance();
        void CaculateMD5Test();

    public:
        ~MD5Test();
        static void Entry();
        static void Exit();
    };
}

