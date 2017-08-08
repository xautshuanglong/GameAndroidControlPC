#pragma once

#include "Log.h"

namespace ShuangLong
{
	namespace Test
	{
		class VersionUtilTest sealed
		{
		private:
			VersionUtilTest();
			Log*                     mpLog;
			static VersionUtilTest  *mpInstance;

		public:
			~VersionUtilTest();

			static void Entry();

			void GetFileVersionInfoTest();
		};
	}
}

