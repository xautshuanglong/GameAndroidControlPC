#pragma once

namespace Shuanglong::Test
{
    class GoogleLogTest
    {
    private:
        GoogleLogTest();
        static GoogleLogTest * GetInstance();

    public:
        ~GoogleLogTest();
        void Initialize(const char* moduleName);
        void Uninitialize();
        void ShowLogMessage();

        static void Entry(const char* moduleName);
        static void Exit();
    };
}

