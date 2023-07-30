#include "stdafx.h"

#include <Utils/TimeUtil.h>
#include <ctime>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Shuanglong::Utils;

namespace NativeUnitTest
{
    TEST_CLASS(TimeUtilTest)
    {
    public:
        TEST_METHOD(GetCurrentTimestampTest)
        {
            time_t curTimeExpect;
            time_t curTimeTest;

            ::time(&curTimeExpect);
            curTimeTest = TimeUtil::GetCurrentTimestamp();

            Assert::AreEqual((int)curTimeExpect, (int)curTimeTest);
        }
    };
}