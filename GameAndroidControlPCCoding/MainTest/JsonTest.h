#pragma once

namespace Shuanglong::Test
{
    class JsonTest
    {
    private:
        JsonTest();
        static JsonTest* GetInstance();

    public:
        ~JsonTest();
        void ReaderTest();
        void WriterTest();
        static void Entry();
        static void Exit();
    };
}
