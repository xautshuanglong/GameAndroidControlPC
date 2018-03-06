#pragma 

#include "Log.h"

namespace Shuanglong
{
    namespace Test
    {
        class WindowsInfoLookerTest sealed
        {
        private:
            Log*                    mpLog;
            
        public:
            ~WindowsInfoLookerTest();
            static WindowsInfoLookerTest*  GetInstance();
            void Entry();
            void Exit();

            void GetSystemInfoTest();

        private:
            WindowsInfoLookerTest();
        };
    }
}
