#include "stdafx.h"
#include "CppUnitTest.h"

#include <TimeUtil.h>
#include <ctime>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ShuangLong::Utils;

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